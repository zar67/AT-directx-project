#include "BlendState.h"
#include "ErrorLogger.h"

BlendState::BlendState(Graphics& graphics, bool blending)
{
	m_blending = blending;

	D3D11_BLEND_DESC blendDescription = {};
	auto& blendRenderTarget = blendDescription.RenderTarget[0];
	if (m_blending)
	{
		blendRenderTarget.BlendEnable = TRUE;
		blendRenderTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendRenderTarget.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendRenderTarget.BlendOp = D3D11_BLEND_OP_ADD;
		blendRenderTarget.SrcBlendAlpha = D3D11_BLEND_ZERO;
		blendRenderTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
		blendRenderTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendRenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}
	else
	{
		blendRenderTarget.BlendEnable = false;
		blendRenderTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}

	HRESULT hResult = graphics.GetDevice()->CreateBlendState(&blendDescription, &m_pBlendState);
	if (FAILED(hResult))
	{
		ErrorLogger::Log(hResult, "Failed to create BlendState.");
	}
}

void BlendState::Bind(Graphics& graphics)
{
	graphics.GetDeviceContext()->OMSetBlendState(m_pBlendState.Get(), nullptr, 0xFFFFFFFFu);
}