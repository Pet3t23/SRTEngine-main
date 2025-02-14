#pragma once
#include "PreRequisites.h"

/**
 * @class DeviceContext
 * @brief Representa un contexto de dispositivo Direct3D para la gestión de estados y recursos gráficos.
 */
class DeviceContext {
public:
    DeviceContext() = default;
    ~DeviceContext() = default;

    /**
     * @brief Inicializa el contexto del dispositivo.
     */
    void init();

    /**
     * @brief Actualiza el estado del contexto.
     */
    void update();

    /**
     * @brief Renderiza los elementos gráficos asociados al contexto.
     */
    void render();

    /**
     * @brief Libera los recursos del contexto.
     */
    void destroy();

    /**
     * @brief Configura las vistas de la pantalla.
     * @param NumViewports Número de viewports.
     * @param pViewports Puntero a la estructura D3D11_VIEWPORT.
     */
    void RSSetViewports(unsigned int NumViewports, const D3D11_VIEWPORT* pViewports);

    /**
     * @brief Configura los recursos de textura para el sombreador de píxeles.
     * @param StartSlot Índice de inicio.
     * @param NumViews Número de vistas.
     * @param ppShaderResourceViews Arreglo de vistas de recursos del sombreador.
     */
    void PSSetShaderResources(unsigned int StartSlot,
        unsigned int NumViews,
        ID3D11ShaderResourceView* const* ppShaderResourceViews);

    /**
     * @brief Establece el diseño de entrada para la etapa de ensamblaje de entrada.
     * @param pInputLayout Puntero al diseño de entrada.
     */
    void IASetInputLayout(ID3D11InputLayout* pInputLayout);

    /**
     * @brief Configura el sombreador de vértices.
     */
    void VSSetShader(ID3D11VertexShader* pVertexShader,
        ID3D11ClassInstance* const* ppClassInstances,
        unsigned int NumClassInstances);

    /**
     * @brief Configura el sombreador de píxeles.
     */
    void PSSetShader(ID3D11PixelShader* pPixelShader,
        ID3D11ClassInstance* const* ppClassInstances,
        unsigned int NumClassInstances);

    /**
     * @brief Actualiza una subrecurso en la GPU.
     */
    void UpdateSubresource(ID3D11Resource* pDstResource,
        unsigned int DstSubresource,
        const D3D11_BOX* pDstBox,
        const void* pSrcData,
        unsigned int SrcRowPitch,
        unsigned int SrcDepthPitch);

    /**
     * @brief Establece los búferes de vértices para la etapa de ensamblaje de entrada.
     */
    void IASetVertexBuffers(unsigned int StartSlot,
        unsigned int NumBuffers,
        ID3D11Buffer* const* ppVertexBuffers,
        const unsigned int* pStrides,
        const unsigned int* pOffsets);

    /**
     * @brief Establece el búfer de índices.
     */
    void IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
        DXGI_FORMAT Format,
        unsigned int Offset);

    /**
     * @brief Configura los muestreadores para el sombreador de píxeles.
     */
    void PSSetSamplers(unsigned int StartSlot,
        unsigned int NumSamplers,
        ID3D11SamplerState* const* ppSamplers);

    /**
     * @brief Establece el estado de rasterización.
     */
    void RSSetState(ID3D11RasterizerState* pRasterizerState);

    /**
     * @brief Configura el estado de mezcla.
     */
    void OMSetBlendState(ID3D11BlendState* pBlendState,
        const float BlendFactor[4],
        unsigned int SampleMask);

    /**
     * @brief Configura los render targets.
     */
    void OMSetRenderTargets(unsigned int NumViews,
        ID3D11RenderTargetView* const* ppRenderTargetViews,
        ID3D11DepthStencilView* pDepthStencilView);

    /**
     * @brief Establece la topología de ensamblaje de primitivas.
     */
    void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);

    /**
     * @brief Limpia la vista de renderizado con un color específico.
     */
    void ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
        const float ColorRGBA[4]);

    /**
     * @brief Limpia la vista de profundidad y esténcil.
     */
    void ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
        unsigned int ClearFlags,
        float Depth,
        UINT8 Stencil);

    /**
     * @brief Configura los búferes constantes para el sombreador de vértices.
     */
    void VSSetConstantBuffers(unsigned int StartSlot,
        unsigned int NumBuffers,
        ID3D11Buffer* const* ppConstantBuffers);

    /**
     * @brief Configura los búferes constantes para el sombreador de píxeles.
     */
    void PSSetConstantBuffers(unsigned int StartSlot,
        unsigned int NumBuffers,
        ID3D11Buffer* const* ppConstantBuffers);

    /**
     * @brief Dibuja un conjunto de índices.
     */
    void DrawIndexed(unsigned int IndexCount,
        unsigned int StartIndexLocation,
        int BaseVertexLocation);

private:
    /**
     * @brief Puntero al contexto del dispositivo Direct3D.
     */
public:
    ID3D11DeviceContext* m_deviceContext = nullptr;
};
