#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"
#include "Device.h"
#include "DeviceContext.h"

/**
 * Inicializa una textura desde un archivo dependiendo de la extensión.
 * Carga la textura y la asigna a la memoria gráfica de la GPU.
 * @param device Dispositivo de DirectX 11 para interactuar con la GPU.
 * @param textureName Nombre del archivo de la textura a cargar.
 * @param extensionType Tipo de extensión del archivo (DDS, PNG).
 * @return HRESULT que indica el éxito o fracaso de la operación.
 */
HRESULT Texture::init(Device device, const std::string& textureName, ExtensionType extensionType) {
    if (!device.m_device) {
        ERROR("Texture", "init", "Device is nullptr in texture loading method");
        return E_POINTER;
    }

    HRESULT hr = S_OK;

    // Dependiendo del tipo de extensión, se maneja de diferente forma
    switch (extensionType) {
    case DDS:
        // Cargar textura DDS utilizando DirectX 11.
        hr = D3DX11CreateShaderResourceViewFromFile(
            device.m_device,
            textureName.c_str(),
            nullptr,
            nullptr,
            &m_textureFromImg,
            nullptr
        );

        if (FAILED(hr)) {
            ERROR("Texture", "init",
                ("Failed to load DDS texture. Verify filepath: " + textureName).c_str());
            return hr;
        }
        break;

    case PNG: {
        int width, height, channels;
        unsigned char* data = stbi_load(textureName.c_str(), &width, &height, &channels, 4); // 4 bytes por pixel (RGBA).
        if (!data) {
            ERROR("Texture", "init",
                ("Failed to load PNG texture: " + std::string(stbi_failure_reason())).c_str());
            return E_FAIL;
        }

        // Crear la descripción de la textura para la GPU.
        D3D11_TEXTURE2D_DESC textureDesc = {};
        textureDesc.Width = width;
        textureDesc.Height = height;
        textureDesc.MipLevels = 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

        // Crear la textura en la GPU usando los datos cargados de la imagen.
        D3D11_SUBRESOURCE_DATA initData = {};
        initData.pSysMem = data;
        initData.SysMemPitch = width * 4;

        hr = device.CreateTexture2D(&textureDesc, &initData, &m_texture);
        stbi_image_free(data); // Liberar la memoria de la imagen.

        if (FAILED(hr)) {
            ERROR("Texture", "init", "Failed to create texture from PNG data");
            return hr;
        }

        // Crear vista del recurso de la textura para ser usado en shaders.
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Format = textureDesc.Format;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = 1;

        hr = device.m_device->CreateShaderResourceView(m_texture, &srvDesc, &m_textureFromImg);
        SAFE_RELEASE(m_texture); // Liberar la textura intermedia.

        if (FAILED(hr)) {
            ERROR("Texture", "init", "Failed to create shader resource view for PNG texture");
            return hr;
        }
        break;
    }

    default:
        ERROR("Texture", "init", "Unsupported extension type");
        return E_INVALIDARG;
    }

    return hr;
}

/**
 * Inicializa una textura con dimensiones y parámetros específicos.
 * Esta función es útil cuando la textura no se carga desde un archivo, sino que se crea manualmente.
 * @param device Dispositivo de DirectX 11 para interactuar con la GPU.
 * @param width Ancho de la textura.
 * @param height Altura de la textura.
 * @param format Formato de la textura (DXGI_FORMAT_*).
 * @param bindFlags Banderas de uso de la textura (ej. D3D11_BIND_SHADER_RESOURCE).
 * @param sampleCount Número de muestras por píxel (para texturas multisample).
 * @param qualityLevels Niveles de calidad de muestreo.
 * @return HRESULT que indica el éxito o fracaso de la operación.
 */
HRESULT Texture::init(Device device,
    unsigned int width,
    unsigned int height,
    DXGI_FORMAT format,
    unsigned int bindFlags,
    unsigned int sampleCount,
    unsigned int qualityLevels) {
    if (!device.m_device) {
        ERROR("Texture", "init", "Device is nullptr in texture initialization method");
        return E_POINTER;
    }
    if (width == 0 || height == 0) {
        ERROR("Texture", "init", "Width and height must be greater than 0");
        return E_INVALIDARG;
    }

    HRESULT hr = S_OK;

    // Configuración de la textura en la GPU.
    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = format;
    desc.SampleDesc.Count = sampleCount;
    desc.SampleDesc.Quality = qualityLevels;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = bindFlags;

    hr = device.CreateTexture2D(&desc, nullptr, &m_texture);
    if (FAILED(hr)) {
        ERROR("Texture", "init", "Failed to create texture with the specified parameters");
        return hr;
    }

    return hr;
}

/**
 * Método para actualizar la textura. Actualmente no realiza ninguna acción, pero se puede implementar
 * futuras actualizaciones o animaciones de la textura.
 */
void Texture::update() {
    // Funcionalidad para actualizar la textura puede ser implementada aquí.
}

/**
 * Método para renderizar la textura en el contexto de dispositivos de DirectX.
 * Asigna la textura al shader del pixel en la etapa de renderizado.
 * @param deviceContext Contexto de dispositivo para la ejecución del comando de renderizado.
 * @param StartSlot Slot inicial de la textura en el shader.
 * @param NumViews Número de vistas del recurso de la textura.
 */
void Texture::render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumViews) {
    if (m_textureFromImg) {
        // Liberar los recursos previos para evitar conflictos.
        ID3D11ShaderResourceView* nullSRV[] = { nullptr };
        deviceContext.PSSetShaderResources(StartSlot, NumViews, nullSRV);
        deviceContext.PSSetShaderResources(StartSlot, NumViews, &m_textureFromImg);
    }
    else {
        ERROR("Texture", "render", "Texture resource is not initialized");
    }
}

/**
 * Libera los recursos utilizados por la textura.
 * Llama a los métodos para liberar la memoria utilizada por la textura y su vista.
 */
void Texture::destroy() {
    SAFE_RELEASE(m_texture);
    SAFE_RELEASE(m_textureFromImg);
}
