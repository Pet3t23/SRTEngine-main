#pragma once
#include "PreRequisites.h"

// Forward declarations
class Device;
class DeviceContext;
class Texture;

/**
 * @brief Vista de profundidad y esténcil en Direct3D.
 */
class DepthStencilView {
public:
    DepthStencilView() = default;
    ~DepthStencilView() = default;

    /**
     * @brief Inicializa la vista de profundidad y esténcil.
     * @return HRESULT Código de éxito o error.
     */
    HRESULT init(Device& device, Texture& depthStencil, DXGI_FORMAT format);

    /**
     * @brief Actualiza la vista de profundidad y esténcil.
     */
    void update();

    /**
     * @brief Renderiza la vista de profundidad y esténcil.
     * @param deviceContext Contexto del dispositivo.
     */
    void render(DeviceContext& deviceContext);

    /**
     * @brief Libera los recursos utilizados.
     */
    void destroy();

public:
    ID3D11DepthStencilView* m_depthStencilView = nullptr; ///< Puntero a la vista de profundidad y esténcil.
};
