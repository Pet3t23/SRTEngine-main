#pragma once
#include "Prerequisites.h"
#include "Window.h"

/**
 * @brief Clase base para la aplicaci�n.
 *
 * Maneja la inicializaci�n, actualizaci�n, renderizado y cierre de la aplicaci�n.
 */
class BaseApp {
public:
    BaseApp() = default;
    ~BaseApp() = default;

    /**
     * @brief Inicializa la aplicaci�n.
     * @return HRESULT Indica si la inicializaci�n fue exitosa.
     */
    HRESULT init();

    /**
     * @brief Actualiza el estado de la aplicaci�n.
     */
    void update();

    /**
     * @brief Renderiza los elementos de la aplicaci�n.
     */
    void render();

    /**
     * @brief Libera los recursos utilizados.
     */
    void destroy();

    /**
     * @brief Ejecuta la aplicaci�n.
     *
     * @param hInstance Instancia de la aplicaci�n.
     * @param hPrevInstance No se usa en Windows moderno.
     * @param lpCmdLine L�nea de comandos.
     * @param nCmdShow Modo de visualizaci�n de la ventana.
     * @param wndproc Funci�n de manejo de eventos de la ventana.
     * @return C�digo de salida de la aplicaci�n.
     */
    int run(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPWSTR lpCmdLine,
        int nCmdShow,
        WNDPROC wndproc);

private:
    Window m_window; ///< Maneja la ventana de la aplicaci�n.
};
