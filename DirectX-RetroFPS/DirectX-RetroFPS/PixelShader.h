/* ------------------------------------------------- */
/* Filename: PixelShader.h                           */
/* Author: Zoe Rowbotham                             */
/* Description: Header of the PixelShader class      */
/* ------------------------------------------------- */

#pragma once
#include "Bindable.h"

class PixelShader : public Bindable
{
public:
	PixelShader(Graphics& graphics, std::wstring shaderPath);
	virtual ~PixelShader() = default;

	virtual void Bind(Graphics& graphics) override;

protected:
	std::wstring m_shaderPath;

	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D10Blob> m_pShaderBuffer = nullptr;
};