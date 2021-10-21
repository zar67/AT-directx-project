#include "InputLayout.h"

InputLayout::InputLayout(Graphics& graphics, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3D10Blob* pVertexShaderByteCode)
{
	HRESULT hResult = graphics.GetDevice()->CreateInputLayout(
		layout.data(), layout.size(),
		pVertexShaderByteCode->GetBufferPointer(), pVertexShaderByteCode->GetBufferSize(),
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
