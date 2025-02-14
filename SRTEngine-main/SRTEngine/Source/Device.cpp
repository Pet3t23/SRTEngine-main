#include "Device.h"

// Libera el dispositivo Direct3D si está asignado.
// Esta función destruye cualquier recurso asignado a 'm_device' para liberar memoria.
void Device::destroy() {
    SAFE_RELEASE(m_device);  // Libera el dispositivo, si existe.
}

// Crea una Render Target View a partir de un recurso.
// pResource: El recurso Direct3D al que se le asignará la vista de renderizado.
// pDesc: Descripción del tipo de vista de renderizado que se creará.
// ppRTView: Puntero de salida que recibe la vista de renderizado creada.
// Devuelve un HRESULT que indica el resultado de la operación.
HRESULT Device::CreateRenderTargetView(ID3D11Resource* pResource,
    const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
    ID3D11RenderTargetView** ppRTView) {

    // Validación de parámetros de entrada.
    if (!pResource) {
        ERROR("Device", "CreateRenderTargetView", "pResource is nullptr");
        return E_INVALIDARG; // Argumento Invalido.
    }

    if (!ppRTView) {
        ERROR("Device", "CreateRenderTargetView", "ppRTView is nullptr");
        return E_POINTER; // Puntero nulo.
    }

    // Crear el Render Target View.
    HRESULT hr = m_device->CreateRenderTargetView(pResource, pDesc, ppRTView);

    if (SUCCEEDED(hr)) {
        MESSAGE("Device", "CreateRenderTargetView", "Render Target View created successfully!");
    }
    else {
        ERROR("Device", "CreateRenderTargetView",
            ("Failed to create Render Target View. HRESULT: " + std::to_string(hr)).c_str());
    }

    return hr;
}

// Crea una textura 2D en la GPU.
// pDesc: Descripción de la textura 2D que se creará.
// pInitialData: Datos iniciales para la textura.
// ppTexture2D: Puntero de salida para la textura 2D creada.
// Devuelve un HRESULT que indica el resultado de la operación.
HRESULT Device::CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
    const D3D11_SUBRESOURCE_DATA* pInitialData,
    ID3D11Texture2D** ppTexture2D) {
    if (!pDesc) {
        ERROR("Device", "CreateTexture2D", "pDesc is nullptr");
        return E_INVALIDARG;
    }
    if (!ppTexture2D) {
        ERROR("Device", "CreateTexture2D", "ppTexture2D is nullptr");
        return E_POINTER;
    }

    HRESULT hr = m_device->CreateTexture2D(pDesc, pInitialData, ppTexture2D);

    if (SUCCEEDED(hr)) {
        MESSAGE("Device", "CreateTexture2D", "Texture2D created successfully");
    }
    else {
        ERROR("Device", "CreateTexture2D",
            ("Failed to create Texture2D. HRESULT: " + std::to_string(hr)).c_str());
    }

    return hr;
}

// Crea una Depth Stencil View para administrar el buffer de profundidad.
// pResource: Recurso de la textura o buffer que contiene la profundidad.
// pDesc: Descripción del tipo de vista de profundidad y stencil que se creará.
// ppDepthStencilView: Puntero de salida para la vista de profundidad y stencil.
// Devuelve un HRESULT que indica el resultado de la operación.
HRESULT Device::CreateDepthStencilView(ID3D11Resource* pResource,
    const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
    ID3D11DepthStencilView** ppDepthStencilView) {
    if (!pResource) {
        ERROR("Device", "CreateDepthStencilView", "pResource is nullptr");
        return E_INVALIDARG;
    }
    if (!ppDepthStencilView) {
        ERROR("Device", "CreateDepthStencilView", "ppDepthStencilView is nullptr");
        return E_POINTER;
    }

    HRESULT hr = m_device->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);

    if (SUCCEEDED(hr)) {
        MESSAGE("Device", "CreateDepthStencilView", "DepthStencilView created successfully");
    }
    else {
        ERROR("Device", "CreateDepthStencilView",
            ("Failed to create DepthStencilView. HRESULT: " + std::to_string(hr)).c_str());
    }

    return hr;
}

// Crea un Vertex Shader a partir del código de shader compilado.
// pShaderBytecode: El bytecode del shader de vértices compilado.
// BytecodeLength: Longitud del bytecode del shader.
// pClassLinkage: (Opcional) Enlaces de clase si son necesarios para el shader.
// ppVertexShader: Puntero de salida que recibe el shader de vértices creado.
// Devuelve un HRESULT que indica el resultado de la operación.
HRESULT Device::CreateVertexShader(const void* pShaderBytecode,
    unsigned int BytecodeLength,
    ID3D11ClassLinkage* pClassLinkage,
    ID3D11VertexShader** ppVertexShader) {
    if (!pShaderBytecode) {
        ERROR("Device", "CreateVertexShader", "pShaderBytecode is nullptr");
        return E_INVALIDARG;
    }
    if (!ppVertexShader) {
        ERROR("Device", "CreateVertexShader", "ppVertexShader is nullptr");
        return E_POINTER;
    }

    HRESULT hr = m_device->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);

    if (SUCCEEDED(hr)) {
        MESSAGE("Device", "CreateVertexShader", "VertexShader created successfully");
    }
    else {
        ERROR("Device", "CreateVertexShader",
            ("Failed to create VertexShader. HRESULT: " + std::to_string(hr)).c_str());
    }

    return hr;
}

// Crea un Input Layout para especificar el formato de los vértices.
// pInputElementDescs: Descripción de los elementos de entrada para los vértices.
// NumElements: Número de elementos en el arreglo de descripciones.
// pShaderBytecodeWithInputSignature: Bytecode del shader con la firma de entrada.
// BytecodeLength: Longitud del bytecode del shader.
// ppInputLayout: Puntero de salida para el layout de entrada creado.
// Devuelve un HRESULT que indica el resultado de la operación.
HRESULT Device::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
    unsigned int NumElements,
    const void* pShaderBytecodeWithInputSignature,
    unsigned int BytecodeLength,
    ID3D11InputLayout** ppInputLayout) {
    if (!pInputElementDescs) {
        ERROR("Device", "CreateInputLayout", "pInputElementDescs is nullptr");
        return E_INVALIDARG;
    }
    if (!ppInputLayout) {
        ERROR("Device", "CreateInputLayout", "ppInputLayout is nullptr");
        return E_POINTER;
    }

    HRESULT hr = m_device->CreateInputLayout(pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);

    if (SUCCEEDED(hr)) {
        MESSAGE("Device", "CreateInputLayout", "InputLayout created successfully");
    }
    else {
        ERROR("Device", "CreateInputLayout",
            ("Failed to create InputLayout. HRESULT: " + std::to_string(hr)).c_str());
    }

    return hr;
}

// Crea un Pixel Shader a partir del código de shader compilado.
// pShaderBytecode: El bytecode del shader de píxel compilado.
// BytecodeLength: Longitud del bytecode del shader.
// pClassLinkage: (Opcional) Enlaces de clase si son necesarios para el shader.
// ppPixelShader: Puntero de salida que recibe el shader de píxel creado.
// Devuelve un HRESULT que indica el resultado de la operación.
HRESULT Device::CreatePixelShader(const void* pShaderBytecode,
    unsigned int BytecodeLength,
    ID3D11ClassLinkage* pClassLinkage,
    ID3D11PixelShader** ppPixelShader) {
    if (!pShaderBytecode) {
        ERROR("Device", "CreatePixelShader", "pShaderBytecode is nullptr");
        return E_INVALIDARG;
    }
    if (!ppPixelShader) {
        ERROR("Device", "CreatePixelShader", "ppPixelShader is nullptr");
        return E_POINTER;
    }

    HRESULT hr = m_device->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);

    if (SUCCEEDED(hr)) {
        MESSAGE("Device", "CreatePixelShader", "PixelShader created successfully");
    }
    else {
        ERROR("Device", "CreatePixelShader",
            ("Failed to create PixelShader. HRESULT: " + std::to_string(hr)).c_str());
    }

    return hr;
}

// Crea un buffer de Direct3D11.
// pDesc: Descripción del buffer que se va a crear.
// pInitialData: Datos iniciales que se copiarán al buffer.
// ppBuffer: Puntero de salida que recibe el buffer creado.
// Devuelve un HRESULT que indica el resultado de la operación.
HRESULT Device::CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
    const D3D11_SUBRESOURCE_DATA* pInitialData,
    ID3D11Buffer** ppBuffer) {
    if (!pDesc) {
        ERROR("Device", "CreateBuffer", "pDesc is nullptr");
        return E_INVALIDARG;
    }
    if (!ppBuffer) {
        ERROR("Device", "CreateBuffer", "ppBuffer is nullptr");
        return E_POINTER;
    }

    HRESULT hr = m_device->CreateBuffer(pDesc, pInitialData, ppBuffer);

    if (SUCCEEDED(hr)) {
        MESSAGE("Device", "CreateBuffer", "Buffer created successfully");
    }
    else {
        ERROR("Device", "CreateBuffer",
            ("Failed to create Buffer. HRESULT: " + std::to_string(hr)).c_str());
    }

    return hr;
}

// Crea un estado de muestreo (Sampler State).
// pSamplerDesc: Descripción del estado de muestreo que se va a crear.
// ppSamplerState: Puntero de salida para el estado de muestreo creado.
// Devuelve un HRESULT que indica el resultado de la operación.
HRESULT Device::CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
    ID3D11SamplerState** ppSamplerState) {
    if (!pSamplerDesc) {
        ERROR("Device", "CreateSamplerState", "pSamplerDesc is nullptr");
        return E_INVALIDARG;
    }
    if (!ppSamplerState) {
        ERROR("Device", "CreateSamplerState", "ppSamplerState is nullptr");
        return E_POINTER;
    }

    HRESULT hr = m_device->CreateSamplerState(pSamplerDesc, ppSamplerState);

    if (SUCCEEDED(hr)) {
        MESSAGE("Device", "CreateSamplerState", "SamplerState created successfully");
    }
    else {
        ERROR("Device", "CreateSamplerState",
            ("Failed to create SamplerState. HRESULT: " + std::to_string(hr)).c_str());
    }

    return hr;
}

// Crea un estado de rasterización (Rasterizer State).
// pRasterizerDesc: Descripción del estado de rasterización que se va a crear.
// ppRasterizerState: Puntero de salida para el estado de rasterización creado.
// Devuelve un HRESULT que indica el resultado de la operación.
HRESULT Device::CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc,
    ID3D11RasterizerState** ppRasterizerState) {
    if (!pRasterizerDesc) {
        ERROR("Device", "CreateRasterizerState", "pRasterizerDesc is nullptr");
        return E_INVALIDARG;
    }
    if (!ppRasterizerState) {
        ERROR("Device", "CreateRasterizerState", "ppRasterizerState is nullptr");
        return E_POINTER;
    }

    HRESULT hr = m_device->CreateRasterizerState(pRasterizerDesc, ppRasterizerState);

    if (SUCCEEDED(hr)) {
        MESSAGE("Device", "CreateRasterizerState", "RasterizerState created successfully");
    }
    else {
        ERROR("Device", "CreateRasterizerState",
            ("Failed to create RasterizerState. HRESULT: " + std::to_string(hr)).c_str());
    }

    return hr;
}

// Crea un estado de mezcla (Blend State).
// pBlendStateDesc: Descripción del estado de mezcla que se va a crear.
// ppBlendState: Puntero de salida para el estado de mezcla creado.
// Devuelve un HRESULT que indica el resultado de la operación.
HRESULT Device::CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc,
    ID3D11BlendState** ppBlendState) {
    if (!pBlendStateDesc) {
        ERROR("Device", "CreateBlendState", "pBlendStateDesc is nullptr");
        return E_INVALIDARG;
    }
    if (!ppBlendState) {
        ERROR("Device", "CreateBlendState", "ppBlendState is nullptr");
        return E_POINTER;
    }

    HRESULT hr = m_device->CreateBlendState(pBlendStateDesc, ppBlendState);

    if (SUCCEEDED(hr)) {
        MESSAGE("Device", "CreateBlendState", "BlendState created successfully");
    }
    else {
        ERROR("Device", "CreateBlendState",
            ("Failed to create BlendState. HRESULT: " + std::to_string(hr)).c_str());
    }

    return hr;
}
