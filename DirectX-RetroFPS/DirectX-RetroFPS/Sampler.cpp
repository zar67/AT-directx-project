#include "Sampler.h"

Sampler::Sampler(Graphics& graphics)
{
	D3D11_SAMPLER_DESC samplerDescription;
	ZeroMemory(&samplerDescription, sizeof(D3D11_SAMPLER_DESC));

	samplerDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescription.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDescription.MinLOD = 0;
	samplerDescription.MaxLOD = D3D11_FLOAT32_MAX;

	HRESULT hResult = graphics.GetDevice()->CreateSamplerState(&samplerDescription, m_pSamplerState.GetAddressOf());
	if (FAILED(hResult))
	{
		ErrorLogger::Log(hResult, "Failed to Create Sampler State.");
	}
}

void Sampler::Bind(Graphics& graphics)
{
	graphics.GetDeviceContext()->PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());
}