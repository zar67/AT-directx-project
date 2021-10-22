#include "TextureBindable.h"
#include "StringConversion.h"
#include "WICTextureLoader.h"

TextureBindable::TextureBindable(Graphics& graphics, std::string filename)
{
	HRESULT hResult = DirectX::CreateWICTextureFromFile(graphics.GetDevice(), StringConversion::StringToWide(filename).c_str(), nullptr, m_pTextureView.GetAddressOf());
	if (FAILED(hResult))
	{
		ErrorLogger::Log(hResult, "Failed to load texture from file: " + filename);
	}
}

void TextureBindable::Bind(Graphics& graphics)
{
	graphics.GetDeviceContext()->PSSetShaderResources(0, 1, m_pTextureView.GetAddressOf());
}