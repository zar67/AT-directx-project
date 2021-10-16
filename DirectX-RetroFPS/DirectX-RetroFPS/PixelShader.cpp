/* ------------------------------------------------- */
/* Filename: PixelShader.cpp                         */
/* Author: Zoe Rowbotham                             */
/* Description: Includes function declarations for   */
/* the PixelShader class.                            */
/* ------------------------------------------------- */

#include "PixelShader.h"

bool PixelShader::Initialise(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderPath)
{
	HRESULT hResult = D3DReadFileToBlob(shaderPath.c_str(), m_pShaderBuffer.GetAddressOf());
	if (FAILED(hResult))
	{
		std::wstring errorMessage = L"Failed to Load Shader: " + shaderPath;
		ErrorLogger::Log(hResult, errorMessage);
		return false;
	}

	hResult = device->CreatePixelShader(
		m_pShaderBuffer->GetBufferPointer(), m_pShaderBuffer->GetBufferSize(),
		NULL, m_pShader.GetAddressOf());

	if (FAILED(hResult))
	{
		std::wstring errorMessage = L"Failed to Create Vertex Shader: " + shaderPath;
		ErrorLogger::Log(hResult, errorMessage);
		return false;
	}
}

ID3D11PixelShader* PixelShader::GetShader()
{
	return m_pShader.Get();
}

ID3D10Blob* PixelShader::GetBuffer()
{
	return m_pShaderBuffer.Get();
}
