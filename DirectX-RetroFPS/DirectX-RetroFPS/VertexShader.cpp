/* ------------------------------------------------- */
/* Filename: VertexShader.cpp                        */
/* Author: Zoe Rowbotham                             */
/* Description: Includes function declarations for   */
/* the VertexShader class.                           */
/* ------------------------------------------------- */

#include "VertexShader.h"

bool VertexShader::Initialise(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderPath, D3D11_INPUT_ELEMENT_DESC* inputElementDescription, int numElements)
{
	HRESULT hResult = D3DReadFileToBlob(shaderPath.c_str(), m_pShaderBuffer.GetAddressOf());
	if (FAILED(hResult))
	{
		std::wstring errorMessage = L"Failed to Load Shader: " + shaderPath;
		ErrorLogger::Log(hResult, errorMessage);
		return false;
	}

	hResult = device->CreateVertexShader(
		m_pShaderBuffer->GetBufferPointer(), m_pShaderBuffer->GetBufferSize(), 
		NULL, m_pShader.GetAddressOf());

	if (FAILED(hResult))
	{
		std::wstring errorMessage = L"Failed to Create Vertex Shader: " + shaderPath;
		ErrorLogger::Log(hResult, errorMessage);
		return false;
	}

	hResult = device->CreateInputLayout(
		inputElementDescription, numElements,
		m_pShaderBuffer->GetBufferPointer(), m_pShaderBuffer->GetBufferSize(),
		m_pInputLayout.GetAddressOf()
	);

	if (FAILED(hResult))
	{
		ErrorLogger::Log(hResult, "Failed to Create Input Layout");
		return false;
	}

	return true;
}

ID3D11VertexShader* VertexShader::GetShader()
{
	return m_pShader.Get();
}

ID3D10Blob* VertexShader::GetBuffer()
{
	return m_pShaderBuffer.Get();
}

ID3D11InputLayout* VertexShader::GetInputLayout()
{
	return m_pInputLayout.Get();
}
