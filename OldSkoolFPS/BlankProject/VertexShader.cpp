/* ------------------------------------------------- */
/* Filename: Shaders.cpp                             */
/* Author: Zoe Rowbotham                             */
/* Description: Includes function declarations for   */
/* the Shaders class.                                */
/* ------------------------------------------------- */

#include "VertexShader.h"

bool VertexShader::Initialise(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderPath)
{
	HRESULT hResult = D3DReadFileToBlob(shaderPath.c_str(), m_shaderBuffer.GetAddressOf());
	if (FAILED(hResult))
	{
		std::wstring errorMessage = L"Failed to Load Shader: " + shaderPath;
		ErrorLogger::Log(hResult, errorMessage);
		return false;
	}

	hResult = device->CreateVertexShader(
		m_shaderBuffer->GetBufferPointer(), m_shaderBuffer->GetBufferSize(), 
		NULL, m_shader.GetAddressOf());

	if (FAILED(hResult))
	{
		std::wstring errorMessage = L"Failed to Create Vertex Shader: " + shaderPath;
		ErrorLogger::Log(hResult, errorMessage);
		return false;
	}

	return true;
}

ID3D11VertexShader* VertexShader::GetShader()
{
	return m_shader.Get();
}

ID3D10Blob* VertexShader::GetBuffer()
{
	return m_shaderBuffer.Get();
}