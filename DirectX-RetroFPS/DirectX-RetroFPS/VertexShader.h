/* ------------------------------------------------- */
/* Filename: Shaders.h                               */
/* Author: Zoe Rowbotham                             */
/* Description: Header of the Shaders class.         */
/* ------------------------------------------------- */

#pragma once
#pragma comment(lib, "D3DCompiler.lib")
#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include "ErrorLogger.h"

class VertexShader
{
public:
	bool Initialise(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderPath, D3D11_INPUT_ELEMENT_DESC* inputDescription, int numElements);
	ID3D11VertexShader* GetShader();
	ID3D10Blob* GetBuffer();
	ID3D11InputLayout* GetInputLayout();

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D10Blob> m_pShaderBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout = nullptr;
};