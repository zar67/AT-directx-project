#include "InputLayout.h"

InputLayout::InputLayout(Graphics& graphics, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3D10Blob* vertexShaderByteCode)
{
	HRESULT hResult = graphics.GetDevice()->CreateInputLayout(
		layout.data(), layout.size(),
		vertexShaderByteCode->GetBufferPointer(), vertexShaderByteCode->GetBufferSize(),
		m_pInputLayout.GetAddressOf()
	);

	if (FAILED(hResult))
	{
		ErrorLogger::Log(hResult, "Failed to Create Input Layout");
	}
}

void InputLayout::Bind(Graphics& graphics)
{
	graphics.GetDeviceContext()->IASetInputLayout(m_pInputLayout.Get());
}
