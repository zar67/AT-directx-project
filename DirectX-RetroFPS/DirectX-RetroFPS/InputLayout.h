#pragma once
#include "Bindable.h"

class InputLayout : public Bindable
{
public:
	InputLayout(
		Graphics& graphics, 
		const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, 
		ID3D10Blob* vertexShaderByteCode
	);
	
	virtual ~InputLayout() = default;

	virtual void Bind(Graphics& graphics) override;

protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout = nullptr;
};