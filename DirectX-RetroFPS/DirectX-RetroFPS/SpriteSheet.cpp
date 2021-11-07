#include "SpriteSheet.h"
#include "StringConversion.h"
#include "WICTextureLoader.h"
#include "ErrorLogger.h"

SpriteSheet::SpriteSheet(Graphics& graphics, std::string filename, int columnCount, int rowCount)
{
	Microsoft::WRL::ComPtr<ID3D11Resource> textureResource;

	HRESULT hResult = DirectX::CreateWICTextureFromFile(graphics.GetDevice(), StringConversion::StringToWide(filename).c_str(), textureResource.GetAddressOf(), m_pTextureView.GetAddressOf());
	if (FAILED(hResult))
	{
		ErrorLogger::Log(hResult, "Failed to load texture from file: " + filename);
	}

	hResult = textureResource->QueryInterface<ID3D11Texture2D>(m_pTexture2D.GetAddressOf());
	if (FAILED(hResult))
	{
		ErrorLogger::Log(hResult, "Failed to get texture from resource.");
	}

	D3D11_TEXTURE2D_DESC textureDescription;
	m_pTexture2D->GetDesc(&textureDescription);

	m_columnCount = columnCount;
	m_rowCount = rowCount;

	m_spriteWidth = textureDescription.Width / columnCount;
	m_spriteHeight = textureDescription.Height / rowCount;
}

void SpriteSheet::Bind(Graphics& graphics)
{
	graphics.GetDeviceContext()->PSSetShaderResources(0, 1, m_pTextureView.GetAddressOf());
}

RECT SpriteSheet::GetSpriteBoundsAtIndex(int index)
{
	RECT rect;
	rect.left = index * m_spriteWidth;
	rect.top = index * m_spriteHeight;
	rect.right = rect.left + m_spriteWidth;
	rect.bottom = rect.top + m_spriteHeight;

	return rect;
}