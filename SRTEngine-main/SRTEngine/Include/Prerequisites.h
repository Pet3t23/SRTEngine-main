#pragma once

// Librerías estándar
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <xnamath.h>
#include <thread>

// Librerías DirectX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "Resource.h"
#include "resource.h"

// MACROS PARA MANEJO DE RECURSOS Y DEPURACIÓN

/**
 * @brief Libera un recurso COM de DirectX si no es nullptr y lo establece en nullptr.
 */
#define SAFE_RELEASE(x) if(x != nullptr) { x->Release(); x = nullptr; }

 /**
  * @brief Registra un mensaje de creación de recursos en la consola de depuración.
  */
#define MESSAGE(classObj, method, state)        \
{                                               \
    std::wostringstream os_;                    \
    os_ << classObj << "::" << method           \
        << " : [CREATION OF RESOURCE : "        \
        << state << "]\n";                      \
    OutputDebugStringW(os_.str().c_str());      \
}

  /**
   * @brief Registra mensajes de error en la consola de depuración.
   */
#define ERROR(classObj, method, errorMSG)                    \
{                                                            \
    try {                                                    \
        std::wostringstream os_;                             \
        os_ << L"ERROR : " << classObj << L"::" << method    \
            << L" : " << errorMSG << L"\n";                  \
        OutputDebugStringW(os_.str().c_str());               \
    } catch (...) {                                          \
        OutputDebugStringW(L"Failed to log error message.\n"); \
    }                                                        \
}

   // ESTRUCTURAS PARA SHADERS Y CONSTANTES

   /**
    * @brief Representa un vértice con posición y coordenadas de textura.
    */
struct SimpleVertex {
    XMFLOAT3 Pos; ///< Posición del vértice.
    XMFLOAT2 Tex; ///< Coordenadas de textura.
};

/**
 * @brief Contiene la matriz de vista para las transformaciones de cámara.
 */
struct CBNeverChanges {
    XMMATRIX mView; ///< Matriz de vista.
};

/**
 * @brief Contiene la matriz de proyección, actualizada en cambios de tamaño de ventana.
 */
struct CBChangeOnResize {
    XMMATRIX mProjection; ///< Matriz de proyección.
};

/**
 * @brief Contiene la matriz del mundo y el color de la malla, que pueden cambiar cada fotograma.
 */
struct CBChangesEveryFrame {
    XMMATRIX mWorld;     ///< Matriz de transformación del mundo.
    XMFLOAT4 vMeshColor; ///< Color de la malla.
};

/**
 * @brief Define los tipos de extensión de imagen compatibles con el sistema.
 */
enum ExtensionType {
    DDS = 0, ///< Formato DDS.
    PNG = 1, ///< Formato PNG.
    JPG = 2  ///< Formato JPG.
};
