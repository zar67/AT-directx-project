#pragma comment(lib, "D3DCompiler.lib")

#include "PixelShader.h"
#include <d3dcompiler.h>

PixelShader::PixelShader(Graphics& graphics, std::wstring shaderPath)
{
	m_shaderPath = shaderPath;

	HRESULT hResult = D3DReadFileToBlob(m_shaderPath.c_str(), m_pShaderBuffer.GetAddressOf());
	if (FAILED(hResult))
	{
		std::wstring errorMessage = L"Failed to Load Shader: " + m_shaderPath;
		ErrorLogger::Log(hResult, errorMessage);
	}

	hResult = graphics.GetDevice()->CreatePixelShader(
		m_pShaderBuffer->GetBufferPointer(), m_pShaderBuffer->GetBufferSize(),
		NULL, m_pShader.GetAddressOf());

	if (FAILED(hResult))
	{
		std::wstring errorMessage = L"Failed to Create Vertex Shader: " + m_shaderPath;
		ErrorLogger::Log(hResult, errorMessage);
	}
}

void PixelShader::Bind(Graphics& graphics)
{
	graphics.GetDeviceContext()->PSSetShader(m_pShader.Get(), NULL, 0);
}