#include "Window.h"

/**
 * Inicializa la ventana de la aplicación.
 * Este método configura la ventana, registra su clase, la crea, y la muestra en la pantalla.
 *
 * @param hInstance Instancia de la aplicación.
 * @param nCmdShow Parametro que indica cómo debe mostrarse la ventana.
 * @param wndproc Función de ventana (procesador de mensajes).
 * @return HRESULT Código de error que indica el estado de la operación:
 *         S_OK si la operación fue exitosa, E_FAIL si ocurrió un error.
 */
HRESULT
Window::init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc) {
	// Almacenar la instancia de la clase.
	m_hInst = hInstance;

	// Registrar la clase de ventana.
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW; // Actualizar la ventana cuando cambia su tamaño.
	wcex.lpfnWndProc = wndproc;           // Función de procesamiento de mensajes.
	wcex.cbClsExtra = 0;                  // No hay datos extra para la clase.
	wcex.cbWndExtra = 0;                  // No hay datos extra para la ventana.
	wcex.hInstance = m_hInst;             // Instancia de la aplicación.
	wcex.hIcon = LoadIcon(m_hInst, (LPCTSTR)IDI_TUTORIAL1); // Ícono de la ventana.
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); // Cursor predeterminado.
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Color de fondo de la ventana.
	wcex.lpszMenuName = NULL; // No se usa menú.
	wcex.lpszClassName = "TutorialWindowClass"; // Nombre de la clase de la ventana.
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1); // Ícono pequeño.

	// Verificar si el registro de la clase falla.
	if (!RegisterClassEx(&wcex)) {
		MessageBox(nullptr, "RegisterClassEx failed!", "Error", MB_OK);
		ERROR("Window", "init", "CHECK FOR RegisterClassEx");
		return E_FAIL; // Si falla, retorna E_FAIL.
	}

	// Crear la ventana con dimensiones predeterminadas.
	RECT rc = { 0, 0, 1200, 1010 }; // Establecer dimensiones de la ventana (1200x1010).
	m_rect = rc;

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE); // Ajustar el tamaño de la ventana para incluir bordes.

	// Crear la ventana con las configuraciones anteriores.
	m_hWnd = CreateWindow("TutorialWindowClass",
		m_windowName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		m_rect.right - m_rect.left,
		m_rect.bottom - m_rect.top,
		NULL,
		NULL,
		m_hInst,
		NULL);

	// Verificar si la creación de la ventana falla.
	if (!m_hWnd) {
		MessageBox(nullptr, "CreateWindow failed!", "Error", MB_OK);
		ERROR("Window", "init", "CHECK FOR CreateWindow()");
		return E_FAIL; // Si falla, retorna E_FAIL.
	}

	// Mostrar y actualizar la ventana.
	ShowWindow(m_hWnd, nCmdShow); // Mostrar la ventana.
	UpdateWindow(m_hWnd); // Actualizar la ventana para reflejar cambios.

	// Configurar las dimensiones del viewport.
	GetClientRect(m_hWnd, &m_rect); // Obtener las dimensiones de la ventana.
	m_width = m_rect.right - m_rect.left; // Ancho de la ventana.
	m_height = m_rect.bottom - m_rect.top; // Alto de la ventana.

	return S_OK; // Retorna éxito si todo sale bien.
}

/**
 * Método vacío para actualizar la ventana.
 * Se puede implementar en el futuro para realizar tareas relacionadas con la actualización del estado de la ventana.
 */
void
Window::update() {
	// Método vacío, no implementado.
}

/**
 * Método vacío para renderizar la ventana.
 * Se puede implementar en el futuro para agregar funcionalidades de renderizado.
 */
void
Window::render() {
	// Método vacío, no implementado.
}

/**
 * Libera los recursos asociados con la ventana.
 * Este método es útil para la limpieza al cerrar la aplicación.
 */
void
Window::destroy() {
	// Método vacío, se puede agregar lógica de destrucción si es necesario.
}
