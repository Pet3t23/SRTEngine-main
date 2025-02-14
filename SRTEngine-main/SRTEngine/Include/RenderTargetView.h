#pragma once
#include "Prerequisites.h"

// Forward Declarations
class Device;
class DeviceContext;
class Texture;
class DepthStencilView;

/**
 * @class RenderTargetView
 * @brief Gestiona un Render Target View (RTV) en Direct3D 11.
 *
 * Un RTV permite renderizar gr�ficos en una textura en lugar de directamente en la pantalla.
 */
class RenderTargetView {
public:
    RenderTargetView() = default;
    ~RenderTargetView() = default;

    /**
     * @brief Inicializa un Render Target View con una textura.
     * @param device Dispositivo Direct3D.
     * @param backBuffer Textura utilizada como render target.
     * @param format Formato de la textura (DXGI_FORMAT).
     * @return HRESULT C�digo de �xito o error.
     */
    HRESULT init(Device& device, Texture& backBuffer, DXGI_FORMAT format);

    /// Actualiza el render target.
    void update();

    /**
     * @brief Renderiza el contenido en el render target.
     * @param deviceContext Contexto del dispositivo.
     * @param depthStencilView Vista de profundidad y est�ncil.
     * @param numViews N�mero de vistas activas.
     * @param clearColor Color de limpieza del render target.
     */
    void render(DeviceContext& deviceContext,
        DepthStencilView& depthStencilView,
        unsigned int numViews,
        const float clearColor[4]);

    /// Libera los recursos del Render Target View.
    void destroy();

public:
    ID3D11RenderTargetView* m_renderTargetView = nullptr;
};
