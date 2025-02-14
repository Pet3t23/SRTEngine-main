#include "BaseApp.h"

/**
 * @brief Inicializa la aplicación.
 *
 * Este método debe ser sobrescrito por las clases derivadas para implementar la inicialización
 * específica de la aplicación, como la creación de dispositivos, carga de recursos, etc.
 *
 * @return HRESULT Indica el estado de la inicialización, donde S_OK indica éxito y un código de error
 * en caso de fallar.
 */
HRESULT
BaseApp::init() {
	// Método no implementado, debe ser sobrescrito en las clases derivadas.
	return E_NOTIMPL;
}

/**
 * @brief Actualiza el estado de la aplicación en cada iteración del bucle principal.
 *
 * Este método debe ser sobrescrito por las clases derivadas para implementar la lógica de actualización
 * de la aplicación, como la entrada del usuario, la física o la lógica de juego.
 */
void
BaseApp::update() {
	// Lógica de actualización de la aplicación.
	// Debe ser implementada en clases derivadas.
}

/**
 * @brief Renderiza el contenido de la aplicación en la pantalla.
 *
 * Este método debe ser sobrescrito por las clases derivadas para implementar el proceso de renderización
 * de la escena, que puede incluir la configuración de las vistas, la presentación de objetos, etc.
 */
void
BaseApp::render() {
	// Lógica de renderización de la aplicación.
	// Debe ser implementada en clases derivadas.
}

/**
 * @brief Libera los recursos utilizados por la aplicación antes de cerrarla.
 *
 * Este método debe ser sobrescrito por las clases derivadas para implementar la limpieza de recursos
 * utilizados, como la liberación de memoria o la destrucción de objetos.
 */
void
BaseApp::destroy() {
	// Lógica para liberar recursos.
	// Debe ser implementada en clases derivadas.
}

/**
 * @brief Ejecuta el bucle principal de la aplicación.
 *
 * Este método maneja el ciclo de vida de la aplicación, gestionando los mensajes de la ventana y ejecutando
 * las funciones de actualización y renderización en el bucle principal.
 *
 * @param hInstance Identificador de la instancia de la aplicación.
 * @param hPrevInstance Identificador de la instancia anterior (no utilizado).
 * @param lpCmdLine Línea de comandos de la aplicación (no utilizada).
 * @param nCmdShow Comando de visualización de la ventana.
 * @param wndproc Función de procesamiento de mensajes de la ventana.
 *
 * @return int Código de salida de la aplicación.
 */
int
BaseApp::run(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow,
	WNDPROC wndproc) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Inicializa la aplicación.
	if (FAILED(init())) {
		destroy();
		return 0;
	}

	// Bucle principal de mensajes y ejecución de la aplicación.
	MSG msg = { 0 };
	while (WM_QUIT != msg.message) {
		// Procesa los mensajes de la ventana.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// Actualiza la lógica de la aplicación y renderiza el contenido.
			update();
			render();
		}
	}

	// Limpieza de recursos antes de salir.
	destroy();

	// Devuelve el código de salida de la aplicación.
	return (int)msg.wParam;
}
