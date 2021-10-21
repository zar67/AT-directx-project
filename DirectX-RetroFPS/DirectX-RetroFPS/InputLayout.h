/* ------------------------------------------------- */
/* Filename: InputLayout.h                           */
/* Author: Zoe Rowbotham                             */
/* Description: Header of the InputLayout class.     */
/* A wrapper for the InputLayout to be easily bound  */
/* to Drawable objects.                              */
/* ------------------------------------------------- */

#pragma once
#include "Bindable.h"

class InputLayout : public Bindable
{
public:
	InputLayout(
		Graphics& graphics, 
		const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, 
		ID3D10Blob* pVertexShaderByteCode
	);
	
	virtual ~InputLayout() = default;

	virtual void Bind(Graphics& graphics) override;

protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout = nullptr;
};