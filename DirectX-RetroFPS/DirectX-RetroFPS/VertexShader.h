/* ------------------------------------------------- */
/* Filename: VertexShader.h                          */
/* Author: Zoe Rowbotham                             */
/* Description: Header of the VertexShader class     */
/* ------------------------------------------------- */

#pragma once
#include "Bindable.h"

class VertexShader : public Bindable
{
public:
	VertexShader(Graphics& graphics, std::wstring shaderPath);
	virtual ~VertexShader() = default;

	virtual void Bind(Graphics & graphics) override;

	ID3D10Blob* GetByteCode();

protected:
	std::wstring m_shaderPath;

	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D10Blob> m_pShaderByteCode = nullptr;
};