#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

class Texture {
public:
    Texture() = default;   // Constructor por defecto.
    ~Texture() = default;  // Destructor por defecto.

    /// <summary>
    /// Brief: Crea una textura a partir de una imagen (.dds) desde nuestro ordenador.
    /// </summary>
    /// <param name="device">: Llamamos al dispositivo para generar los recursos en memoria.</param>
    /// <param name="textureName">: Nombre de la textura, para cargarla desde memoria.</param>
    /// <param name="extensionType">: Tipo de extensión de la imagen (ejemplo: DDS, PNG, JPG).</param>
    HRESULT init(Device device,
        const std::string& textureName,
        ExtensionType extensionType);

    /// <summary>
    /// Brief: Este método es responsable de crear una textura 2D a partir de los datos proporcionados por el desarrollador.
    /// </summary>
    /// <param name="device">: Proporciona los recursos para crear la textura 2D.</param>
    /// <param name="width">: Ancho de la textura (por ejemplo, la ventana de la pantalla).</param>
    /// <param name="height">: Alto de la textura (por ejemplo, la altura de la ventana de la pantalla).</param>
    /// <param name="Format">: Formato de la textura (clasificación para los espacios de bits en memoria).</param>
    /// <param name="BindFlags">: Clasificación del tipo de textura que se está creando.</param>
    HRESULT init(Device device,
        unsigned int width,
        unsigned int height,
        DXGI_FORMAT Format,
        unsigned int BindFlags,
        unsigned int sampleCount = 1,
        unsigned int qualityLevels = 0);

    /// <summary>
    /// Brief: Este método es responsable de actualizar la lógica de la textura.
    /// </summary>
    void update();

    /// <summary>
    /// Brief: Este método es responsable de dibujar los recursos en la pantalla (solo si es necesario).
    /// </summary>
    /// <param name="deviceContext">: Asigna los recursos que se van a usar.</param>
    /// <param name="StartSlot">: Asigna el punto de inicio en memoria (evitar que se solape con otros recursos).</param>
    void render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumViews);

    /// <summary>
    /// Brief: Este método libera los recursos almacenados en la memoria de la clase.
    /// </summary>
    void destroy();

public:
    // Esta variable maneja el recurso de la textura como datos.
    ID3D11Texture2D* m_texture = nullptr;

    // Esta variable maneja el recurso de la textura como datos de imagen.
    ID3D11ShaderResourceView* m_textureFromImg = nullptr;
};
