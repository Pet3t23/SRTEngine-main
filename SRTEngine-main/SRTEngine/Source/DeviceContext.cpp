#include "DeviceContext.h"

// Libera los recursos del contexto del dispositivo.
void
DeviceContext::destroy() {
	// Liberamos el contexto del dispositivo, asegurándonos de que no haya fugas de memoria.
	SAFE_RELEASE(m_deviceContext);
}

// Configura las dimensiones y características de las viewports.
void
DeviceContext::RSSetViewports(unsigned int NumViewports,
	const D3D11_VIEWPORT* pViewports) {
	// Validamos que el puntero a las viewports no sea nulo.
	if (!pViewports) {
		ERROR("DeviceContext", "RSSetViewports", "pViewports is nullptr");
		return;
	}
	// Configuramos las viewports en el contexto de dispositivo.
	m_deviceContext->RSSetViewports(NumViewports, pViewports);
}

// Establece los recursos de shader para la etapa del pixel shader.
void
DeviceContext::PSSetShaderResources(unsigned int StartSlot,
	unsigned int NumViews,
	ID3D11ShaderResourceView* const* ppShaderResourceViews) {

	// Verificamos que el puntero a los recursos de shader no sea nulo.
	if (!ppShaderResourceViews) {
		ERROR("DeviceContext", "PSSetShaderResources", "ppShaderResourceViews is nullptr");
		return;
	}
	// Configuramos los recursos de shader para el pixel shader.
	m_deviceContext->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

// Define la estructura de entrada de los vértices.
void
DeviceContext::IASetInputLayout(ID3D11InputLayout* pInputLayout) {
	// Verificamos que el puntero al layout de entrada no sea nulo.
	if (!pInputLayout) {
		ERROR("DeviceContext", "IASetInputLayout", "pInputLayout is nullptr");
		return;
	}
	// Establecemos el layout de entrada en el contexto de dispositivo.
	m_deviceContext->IASetInputLayout(pInputLayout);
}

// Establece el shader de vértices.
void
DeviceContext::VSSetShader(ID3D11VertexShader* pVertexShader,
	ID3D11ClassInstance* const* ppClassInstances,
	unsigned int NumClassInstances) {
	// Comprobamos si el shader de vértices es válido.
	if (!pVertexShader) {
		ERROR("DeviceContext", "VSSetShader", "pVertexShader is nullptr");
		return;
	}
	// Establecemos el shader de vértices en el contexto de dispositivo.
	m_deviceContext->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
}

// Establece el shader de píxeles.
void
DeviceContext::PSSetShader(ID3D11PixelShader* pPixelShader,
	ID3D11ClassInstance* const* ppClassInstances,
	unsigned int NumClassInstances) {
	// Verificamos que el puntero al shader de píxeles no sea nulo.
	if (!pPixelShader) {
		ERROR("DeviceContext", "PSSetShader", "pPixelShader is nullptr");
		return;
	}
	// Establecemos el shader de píxeles en el contexto de dispositivo.
	m_deviceContext->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
}

// Actualiza una subrecurso de la GPU con datos en la CPU.
void
DeviceContext::UpdateSubresource(ID3D11Resource* pDstResource,
	unsigned int DstSubresource,
	const D3D11_BOX* pDstBox,
	const void* pSrcData,
	unsigned int SrcRowPitch,
	unsigned int SrcDepthPitch) {

	// Comprobamos si los punteros a los recursos de destino o los datos de origen son nulos.
	if (!pDstResource || !pSrcData) {
		ERROR("DeviceContext", "UpdateSubresource",
			"Invalid arguments: pDstResource or pSrcData is nullptr");
		return;
	}
	// Actualizamos el recurso de la GPU con los datos provenientes de la CPU.
	m_deviceContext->UpdateSubresource(pDstResource,
		DstSubresource,
		pDstBox,
		pSrcData,
		SrcRowPitch,
		SrcDepthPitch);
}

// Configura los búferes de vértices para la etapa de entrada de la tubería gráfica.
void
DeviceContext::IASetVertexBuffers(unsigned int StartSlot,
	unsigned int NumBuffers,
	ID3D11Buffer* const* ppVertexBuffers,
	const unsigned int* pStrides,
	const unsigned int* pOffsets) {

	// Verificamos que los punteros a los búferes de vértices, strides y offsets no sean nulos.
	if (!ppVertexBuffers || !pStrides || !pOffsets) {
		ERROR("DeviceContext", "IASetVertexBuffers",
			"Invalid arguments: ppVertexBuffers, pStrides, or pOffsets is nullptr");
		return;
	}
	// Configuramos los búferes de vértices en el contexto de dispositivo.
	m_deviceContext->IASetVertexBuffers(StartSlot,
		NumBuffers,
		ppVertexBuffers,
		pStrides,
		pOffsets);
}

// Establece el búfer de índices para la etapa de entrada de la tubería gráfica.
void
DeviceContext::IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
	DXGI_FORMAT Format,
	unsigned int Offset) {

	// Verificamos si el búfer de índices es válido.
	if (!pIndexBuffer) {
		ERROR("DeviceContext", "IASetIndexBuffer", "pIndexBuffer is nullptr");
		return;
	}
	// Establecemos el búfer de índices en el contexto de dispositivo.
	m_deviceContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
}

// Configura los estados de muestreo para la etapa de píxeles en la tubería gráfica.
void
DeviceContext::PSSetSamplers(unsigned int StartSlot,
	unsigned int NumSamplers,
	ID3D11SamplerState* const* ppSamplers) {

	// Verificamos que el puntero a los samplers no sea nulo.
	if (!ppSamplers) {
		ERROR("DeviceContext", "PSSetSamplers", "ppSamplers is nullptr");
		return;
	}
	// Establecemos los estados de muestreo en el contexto de dispositivo.
	m_deviceContext->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

// Configura el estado de rasterización en la tubería gráfica.
void
DeviceContext::RSSetState(ID3D11RasterizerState* pRasterizerState) {
	// Verificamos que el puntero al estado de rasterización no sea nulo.
	if (!pRasterizerState) {
		ERROR("DeviceContext", "RSSetState", "pRasterizerState is nullptr");
		return;
	}
	// Establecemos el estado de rasterización en el contexto de dispositivo.
	m_deviceContext->RSSetState(pRasterizerState);
}

// Configura el estado de mezcla de la etapa de salida de la tubería gráfica.
void
DeviceContext::OMSetBlendState(ID3D11BlendState* pBlendState,
	const float BlendFactor[4],
	unsigned int SampleMask) {

	// Verificamos que el puntero al estado de mezcla no sea nulo.
	if (!pBlendState) {
		ERROR("DeviceContext", "OMSetBlendState", "pBlendState is nullptr");
		return;
	}
	// Establecemos el estado de mezcla en el contexto de dispositivo.
	m_deviceContext->OMSetBlendState(pBlendState, BlendFactor, SampleMask);
}

// Configura los objetivos de renderizado y el buffer de profundidad en la etapa de salida.
void
DeviceContext::OMSetRenderTargets(unsigned int NumViews,
	ID3D11RenderTargetView* const* ppRenderTargetViews,
	ID3D11DepthStencilView* pDepthStencilView) {

	// Validamos los parámetros de las vistas de renderizado y el depth stencil.
	if (!ppRenderTargetViews && !pDepthStencilView) {
		ERROR("DeviceContext", "OMSetRenderTargets",
			"Both ppRenderTargetViews and pDepthStencilView are nullptr");
		return;
	}

	if (NumViews > 0 && !ppRenderTargetViews) {
		ERROR("DeviceContext", "OMSetRenderTargets",
			"ppRenderTargetViews is nullptr, but NumViews > 0");
		return;
	}

	// Asignamos los objetivos de renderizado y el depth stencil en el contexto de dispositivo.
	m_deviceContext->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
}

// Establece la topología primitiva para la etapa de entrada de la tubería gráfica.
void
DeviceContext::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology) {
	// Validamos que la topología no sea indefinida.
	if (Topology == D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED) {
		ERROR("DeviceContext", "IASetPrimitiveTopology",
			"Topology is D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED");
		return;
	}

	// Establecemos la topología en el contexto de dispositivo.
	m_deviceContext->IASetPrimitiveTopology(Topology);
}

// Limpia la vista del objetivo de renderizado.
void
DeviceContext::ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
	const float ColorRGBA[4]) {
	// Verificamos que los parámetros sean válidos.
	if (!pRenderTargetView) {
		ERROR("DeviceContext", "ClearRenderTargetView", "pRenderTargetView is nullptr");
		return;
	}
	if (!ColorRGBA) {
		ERROR("DeviceContext", "ClearRenderTargetView", "ColorRGBA is nullptr");
		return;
	}

	// Limpiamos el objetivo de renderizado con el color proporcionado.
	m_deviceContext->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
}

// Limpia la vista del Depth Stencil.
void
DeviceContext::ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
	unsigned int ClearFlags,
	float Depth,
	UINT8 Stencil) {

	// Verificamos que el puntero a DepthStencilView sea válido.
	if (!pDepthStencilView) {
		ERROR("DeviceContext", "ClearDepthStencilView",
			"pDepthStencilView is nullptr");
		return;
	}

	// Comprobamos las banderas de limpieza.
	if ((ClearFlags & (D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL)) == 0) {
		ERROR("DeviceContext", "ClearDepthStencilView",
			"Invalid ClearFlags: must include D3D11_CLEAR_DEPTH or D3D11_CLEAR_STENCIL");
		return;
	}

	// Limpiamos el Depth Stencil con las banderas y valores proporcionados.
	m_deviceContext->ClearDepthStencilView(pDepthStencilView, ClearFlags, Depth, Stencil);
}

// Establece los búferes constantes para el shader de vértices.
void
DeviceContext::VSSetConstantBuffers(unsigned int StartSlot,
	unsigned int NumBuffers,
	ID3D11Buffer* const* ppConstantBuffers) {

	// Verificamos que los búferes constantes no sean nulos.
	if (!ppConstantBuffers) {
		ERROR("DeviceContext", "VSSetConstantBuffers", "ppConstantBuffers is nullptr");
		return;
	}

	// Asignamos los búferes constantes al Vertex Shader.
	m_deviceContext->VSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

// Establece los búferes constantes para el pixel shader.
void
DeviceContext::PSSetConstantBuffers(unsigned int StartSlot,
	unsigned int NumBuffers,
	ID3D11Buffer* const* ppConstantBuffers) {

	// Verificamos que los búferes constantes no sean nulos.
	if (!ppConstantBuffers) {
		ERROR("DeviceContext", "PSSetConstantBuffers", "ppConstantBuffers is nullptr");
		return;
	}

	// Asignamos los búferes constantes al Pixel Shader.
	m_deviceContext->PSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

// Dibuja los índices de los vértices.
void
DeviceContext::DrawIndexed(unsigned int IndexCount,
	unsigned int StartIndexLocation,
	int BaseVertexLocation) {

	// Verificamos que el número de índices sea válido.
	if (IndexCount == 0) {
		ERROR("DeviceContext", "DrawIndexed", "IndexCount is zero");
		return;
	}

	// Ejecutamos el comando para dibujar los índices de vértices.
	m_deviceContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}
