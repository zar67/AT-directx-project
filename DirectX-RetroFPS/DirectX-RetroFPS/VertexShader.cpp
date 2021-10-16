/* ------------------------------------------------- */
/* Filename: VertexShader.cpp                        */
/* Author: Zoe Rowbotham                             */
/* Description: Includes function declarations for   */
/* the VertexShader class.                           */
/* ------------------------------------------------- */

#pragma comment(lib, "D3DCompiler.lib")

#include "VertexShader.h"
#include <d3dcompiler.h>

VertexShader::VertexShader(Graphics& graphics, std::wstring shaderPath)
{
	m_shaderPath = shaderPath;

	HRESULT hResult = D3DReadFileToBlob(m_shaderPath.c_str(), m_pShaderByteCode.GetAddressOf());
	if (FAILED(hResult))
	{
		std::wstring errorMessage = L"Failed to Load Shader: " + m_shaderPath;
		ErrorLogger::Log(hResult, errorMessage);
	}

	hResult = graphics.GetDevice()->CreateVertexShader(
		m_pShaderByteCode->GetBufferPointer(), m_pShaderByteCode->GetBufferSize(),
		NULL, m_pShader.GetAddressOf());

	if (FAILED(hResult))
	{
		std::wstring errorMessage = L"Failed to Create Vertex Shader: " + m_shaderPath;
		ErrorLogger::Log(hResult, errorMessage);
	}
}

void VertexShader::Bind(Graphics& graphics)
{
	graphics.GetDeviceContext()->VSSetShader(m_pShader.Get(), NULL, 0);
}

ID3D10Blob* VertexShader::GetByteCode()
{
	return m_pShaderByteCode.Get();
}
