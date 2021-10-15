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
	bool Initialise(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderPath);
	ID3D11VertexShader* GetShader();
	ID3D10Blob* GetBuffer();

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_shader = nullptr;
	Microsoft::WRL::ComPtr<ID3D10Blob> m_shaderBuffer = nullptr;
};