#include "RasterizerState.h"

RasterizerState::RasterizerState(Graphics& graphics)
{
	D3D11_RASTERIZER_DESC rasterizerDescription;
	ZeroMemory(&rasterizerDescription, sizeof(D3D11_RASTERIZER_DESC));

	rasterizerDescription.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDescription.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	HRESULT hResult = graphics.GetDevice()->CreateRasterizerState(&rasterizerDescription, m_pRasterizerState.GetAddressOf());
	if (FAILED(hResult))
	{
		ErrorLogger::Log(hResult, "Failed to Create Rasterizer State");
		return;
	}
}

void RasterizerState::Bind(Graphics& graphics)
{
	graphics.GetDeviceContext()->RSSetState(m_pRasterizerState.Get());
}