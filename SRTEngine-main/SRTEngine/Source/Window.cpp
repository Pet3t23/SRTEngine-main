#include "Window.h"

/**
 * Inicializa la ventana de la aplicaci�n.
 * Este m�todo configura la ventana, registra su clase, la crea, y la muestra en la pantalla.
 *
 * @param hInstance Instancia de la aplicaci�n.
 * @param nCmdShow Parametro que indica c�mo debe mostrarse la ventana.
 * @param wndproc Funci�n de ventana (procesador de mensajes).
 * @return HRESULT C�digo de error que indica el estado de la operaci�n:
 *         S_OK si la operaci�n fue exitosa, E_FAIL si ocurri� un error.
 */
HRESULT
Window::init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc) {
	// Almacenar la instancia de la clase.
	m_hInst = hInstance;

	// Registrar la clase de ventana.
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW; // Actualizar la ventana cuando cambia su tama�o.
	wcex.lpfnWndProc = wndproc;           // Funci�n de procesamiento de mensajes.
	wcex.cbClsExtra = 0;                  // No hay datos extra para la clase.
	wcex.cbWndExtra = 0;                  // No hay datos extra para la ventana.
	wcex.hInstance = m_hInst;             // Instancia de la aplicaci�n.
	wcex.hIcon = LoadIcon(m_hInst, (LPCTSTR)IDI_TUTORIAL1); // �cono de la ventana.
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); // Cursor predeterminado.
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Color de fondo de la ventana.
	wcex.lpszMenuName = NULL; // No se usa men�.
	wcex.lpszClassName = "TutorialWindowClass"; // Nombre de la clase de la ventana.
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1); // �cono peque�o.

	// Verificar si el registro de la clase falla.
	if (!RegisterClassEx(&wcex)) {
		MessageBox(nullptr, "RegisterClassEx failed!", "Error", MB_OK);
		ERROR("Window", "init", "CHECK FOR RegisterClassEx");
		return E_FAIL; // Si falla, retorna E_FAIL.
	}

	// Crear la ventana con dimensiones predeterminadas.
	RECT rc = { 0, 0, 1200, 1010 }; // Establecer dimensiones de la ventana (1200x1010).
	m_rect = rc;

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE); // Ajustar el tama�o de la ventana para incluir bordes.

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

	// Verificar si la creaci�n de la ventana falla.
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

	return S_OK; // Retorna �xito si todo sale bien.
}

/**
 * M�todo vac�o para actualizar la ventana.
 * Se puede implementar en el futuro para realizar tareas relacionadas con la actualizaci�n del estado de la ventana.
 */
void
Window::update() {
	// M�todo vac�o, no implementado.
}

/**
 * M�todo vac�o para renderizar la ventana.
 * Se puede implementar en el futuro para agregar funcionalidades de renderizado.
 */
void
Window::render() {
	// M�todo vac�o, no implementado.
}

/**
 * Libera los recursos asociados con la ventana.
 * Este m�todo es �til para la limpieza al cerrar la aplicaci�n.
 */
void
Window::destroy() {
	// M�todo vac�o, se puede agregar l�gica de destrucci�n si es necesario.
}
