#pragma once
#include "Prerequisites.h"
#include "Window.h"

/**
 * @brief Clase base para la aplicación.
 *
 * Maneja la inicialización, actualización, renderizado y cierre de la aplicación.
 */
class BaseApp {
public:
    BaseApp() = default;
    ~BaseApp() = default;

    /**
     * @brief Inicializa la aplicación.
     * @return HRESULT Indica si la inicialización fue exitosa.
     */
    HRESULT init();

    /**
     * @brief Actualiza el estado de la aplicación.
     */
    void update();

    /**
     * @brief Renderiza los elementos de la aplicación.
     */
    void render();

    /**
     * @brief Libera los recursos utilizados.
     */
    void destroy();

    /**
     * @brief Ejecuta la aplicación.
     *
     * @param hInstance Instancia de la aplicación.
     * @param hPrevInstance No se usa en Windows moderno.
     * @param lpCmdLine Línea de comandos.
     * @param nCmdShow Modo de visualización de la ventana.
     * @param wndproc Función de manejo de eventos de la ventana.
     * @return Código de salida de la aplicación.
     */
    int run(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPWSTR lpCmdLine,
        int nCmdShow,
        WNDPROC wndproc);

private:
    Window m_window; ///< Maneja la ventana de la aplicación.
};
