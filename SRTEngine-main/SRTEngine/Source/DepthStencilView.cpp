#include "DepthStencilView.h"
#include "Device.h"
#include "DeviceContext.h"
#include "Texture.h"

//  Inicializa la vista de Depth Stencil.
//  @param device Referencia al objeto Device que proporciona los recursos del dispositivo.
//  @param depthStencil Referencia a la textura de Depth Stencil que será usada.
//  @param format Formato DXGI que especifica el formato de la textura de Depth Stencil.
//  @return HRESULT Indicando el éxito o error en la inicialización. 
//  Si la creación falla, se devolverá un código de error.
HRESULT DepthStencilView::init(Device& device, Texture& depthStencil, DXGI_FORMAT format) {
    // Verifica si el dispositivo es válido.
    if (!device.m_device) {
        ERROR("DepthStencilView", "init", "Device is nullptr");
        return E_POINTER;
    }

    // Verifica si la textura de Depth Stencil es válida.
    if (!depthStencil.m_texture) {
        ERROR("DepthStencilView", "init", "DepthStencil texture is nullptr");
        return E_POINTER;
    }

    HRESULT hr = S_OK;

    // Configurar la descripción de la vista del Depth Stencil.
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    memset(&descDSV, 0, sizeof(descDSV));
    descDSV.Format = format; // Establece el formato de la vista de Depth Stencil.
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS; // Configura la vista para una textura 2D con múltiples muestras.
    descDSV.Texture2D.MipSlice = 0; // Establece el nivel de mipmap (0 indica el primer nivel).

    // Crear la Depth Stencil View usando el dispositivo y la descripción configurada.
    hr = device.CreateDepthStencilView(depthStencil.m_texture, &descDSV, &m_depthStencilView);
    if (FAILED(hr)) {
        ERROR("DepthStencilView", "init", "Failed to create DepthStencilView");
        return hr;
    }

    return S_OK; // Devuelve éxito si todo sale bien.
}

// Renderiza el Depth Stencil View, limpiando la textura de Depth Stencil.
// @param deviceContext Referencia al contexto del dispositivo utilizado para el renderizado.
// Esta función limpia la vista de Depth Stencil usando valores predeterminados (1.0 para profundidad y 0 para stencil).
void DepthStencilView::render(DeviceContext& deviceContext) {
    // Verifica si la DepthStencilView es válida.
    if (!m_depthStencilView) {
        ERROR("DepthStencilView", "render", "DepthStencilView is nullptr");
        return;
    }

    // Verifica si el contexto del dispositivo es válido.
    if (!deviceContext.m_deviceContext) {
        ERROR("DepthStencilView", "render", "DeviceContext is nullptr");
        return;
    }

    // Limpiar el Depth Stencil View (restablece su valor a los valores iniciales).
    deviceContext.ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

// Libera los recursos asociados al Depth Stencil View.
// Se llama para liberar la memoria y recursos utilizados por la vista de Depth Stencil.
void DepthStencilView::destroy() {
    // Llama a la macro SAFE_RELEASE para liberar el recurso de manera segura.
    SAFE_RELEASE(m_depthStencilView);
}
