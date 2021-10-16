/* ------------------------------------------------- */
/* Filename: PixelShader.h                           */
/* Author: Zoe Rowbotham                             */
/* Description: Header of the PixelShader class      */
/* ------------------------------------------------- */

#pragma once
#pragma comment(lib, "D3DCompiler.lib")
#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include "ErrorLogger.h"

class PixelShader
{
public:
	bool Initialise(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderPath);
	ID3D11PixelShader* GetShader();
	ID3D10Blob* GetBuffer();

private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D10Blob> m_pShaderBuffer = nullptr;
};