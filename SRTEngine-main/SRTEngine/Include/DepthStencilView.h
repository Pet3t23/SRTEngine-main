#pragma once
#include "PreRequisites.h"

// Forward declarations
class Device;
class DeviceContext;
class Texture;

/**
 * @brief Vista de profundidad y est�ncil en Direct3D.
 */
class DepthStencilView {
public:
    DepthStencilView() = default;
    ~DepthStencilView() = default;

    /**
     * @brief Inicializa la vista de profundidad y est�ncil.
     * @return HRESULT C�digo de �xito o error.
     */
    HRESULT init(Device& device, Texture& depthStencil, DXGI_FORMAT format);

    /**
     * @brief Actualiza la vista de profundidad y est�ncil.
     */
    void update();

    /**
     * @brief Renderiza la vista de profundidad y est�ncil.
     * @param deviceContext Contexto del dispositivo.
     */
    void render(DeviceContext& deviceContext);

    /**
     * @brief Libera los recursos utilizados.
     */
    void destroy();

public:
    ID3D11DepthStencilView* m_depthStencilView = nullptr; ///< Puntero a la vista de profundidad y est�ncil.
};
