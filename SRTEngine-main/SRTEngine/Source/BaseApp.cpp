#include "BaseApp.h"

/**
 * @brief Inicializa la aplicaci�n.
 *
 * Este m�todo debe ser sobrescrito por las clases derivadas para implementar la inicializaci�n
 * espec�fica de la aplicaci�n, como la creaci�n de dispositivos, carga de recursos, etc.
 *
 * @return HRESULT Indica el estado de la inicializaci�n, donde S_OK indica �xito y un c�digo de error
 * en caso de fallar.
 */
HRESULT
BaseApp::init() {
	// M�todo no implementado, debe ser sobrescrito en las clases derivadas.
	return E_NOTIMPL;
}

/**
 * @brief Actualiza el estado de la aplicaci�n en cada iteraci�n del bucle principal.
 *
 * Este m�todo debe ser sobrescrito por las clases derivadas para implementar la l�gica de actualizaci�n
 * de la aplicaci�n, como la entrada del usuario, la f�sica o la l�gica de juego.
 */
void
BaseApp::update() {
	// L�gica de actualizaci�n de la aplicaci�n.
	// Debe ser implementada en clases derivadas.
}

/**
 * @brief Renderiza el contenido de la aplicaci�n en la pantalla.
 *
 * Este m�todo debe ser sobrescrito por las clases derivadas para implementar el proceso de renderizaci�n
 * de la escena, que puede incluir la configuraci�n de las vistas, la presentaci�n de objetos, etc.
 */
void
BaseApp::render() {
	// L�gica de renderizaci�n de la aplicaci�n.
	// Debe ser implementada en clases derivadas.
}

/**
 * @brief Libera los recursos utilizados por la aplicaci�n antes de cerrarla.
 *
 * Este m�todo debe ser sobrescrito por las clases derivadas para implementar la limpieza de recursos
 * utilizados, como la liberaci�n de memoria o la destrucci�n de objetos.
 */
void
BaseApp::destroy() {
	// L�gica para liberar recursos.
	// Debe ser implementada en clases derivadas.
}

/**
 * @brief Ejecuta el bucle principal de la aplicaci�n.
 *
 * Este m�todo maneja el ciclo de vida de la aplicaci�n, gestionando los mensajes de la ventana y ejecutando
 * las funciones de actualizaci�n y renderizaci�n en el bucle principal.
 *
 * @param hInstance Identificador de la instancia de la aplicaci�n.
 * @param hPrevInstance Identificador de la instancia anterior (no utilizado).
 * @param lpCmdLine L�nea de comandos de la aplicaci�n (no utilizada).
 * @param nCmdShow Comando de visualizaci�n de la ventana.
 * @param wndproc Funci�n de procesamiento de mensajes de la ventana.
 *
 * @return int C�digo de salida de la aplicaci�n.
 */
int
BaseApp::run(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow,
	WNDPROC wndproc) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Inicializa la aplicaci�n.
	if (FAILED(init())) {
		destroy();
		return 0;
	}

	// Bucle principal de mensajes y ejecuci�n de la aplicaci�n.
	MSG msg = { 0 };
	while (WM_QUIT != msg.message) {
		// Procesa los mensajes de la ventana.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// Actualiza la l�gica de la aplicaci�n y renderiza el contenido.
			update();
			render();
		}
	}

	// Limpieza de recursos antes de salir.
	destroy();

	// Devuelve el c�digo de salida de la aplicaci�n.
	return (int)msg.wParam;
}
