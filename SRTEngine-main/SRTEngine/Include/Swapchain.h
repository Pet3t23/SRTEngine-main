#pragma once
#include "Prerequisites.h"

// Declaraciones adelantadas de clases necesarias
class Device;
class DeviceContext;
class Window;
class Texture;

// Clase que maneja el intercambio de buffers en DirectX 11.
class SwapChain {
public:
    SwapChain() = default;     // Constructor por defecto.
    ~SwapChain() = default;     // Destructor por defecto.

    /**
     * @brief Inicializa la cadena de intercambio.
     * @param device El dispositivo DirectX para interactuar con la GPU.
     * @param deviceContext El contexto del dispositivo para enviar comandos de dibujo.
     * @param backBuffer La textura que servirá como buffer trasero.
     * @param window La ventana donde se va a mostrar la imagen renderizada.
     * @return HRESULT Código de error si la inicialización falla.
     */
    HRESULT init(Device& device,
        DeviceContext& deviceContext,
        Texture& backBuffer,
        Window window);

    // Actualiza el estado de la cadena de intercambio.
    void update();

    // Renderiza el contenido al buffer de la cadena de intercambio.
    void render();

    // Libera los recursos utilizados por la cadena de intercambio.
    void destroy();

    // Muestra el buffer trasero en la pantalla.
    void present();

public:
    IDXGISwapChain* m_swapchain = nullptr;  // Interfaz de la cadena de intercambio.
    D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;  // Tipo de driver Direct3D.

private:
    D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;  // Nivel de características de Direct3D.

    // Configuración de Anti-Aliasing con MSAA.
    unsigned int m_sampleCount;  // Número de muestras MSAA (ej. 4x MSAA).
    unsigned int m_qualityLevels;  // Niveles de calidad del MSAA.

    // Punteros a interfaces DXGI para interactuar con la GPU.
    IDXGIDevice* m_dxgiDevice = nullptr;
    IDXGIAdapter* m_dxgiAdapter = nullptr;
    IDXGIFactory* m_dxgiFactory = nullptr;
};
