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

	m_fileWidth = textureDescription.Width;
	m_fileHeight = textureDescription.Height;

	m_spriteWidth = m_fileWidth / columnCount;
	m_spriteHeight = m_fileHeight / rowCount;
}

void SpriteSheet::Bind(Graphics& graphics)
{
	graphics.GetDeviceContext()->PSSetShaderResources(0, 1, m_pTextureView.GetAddressOf());
}

SpriteSheet::SpriteBounds SpriteSheet::GetSpriteBoundsAtIndex(int index)
{
	float xPos = (index % m_columnCount) * m_spriteWidth;
	float yPos = (index / m_columnCount) * m_spriteHeight;

	SpriteBounds rect;
	rect.Left = xPos / m_fileWidth;
	rect.Top = yPos / m_fileHeight;
	rect.Right = (xPos + m_spriteWidth) / m_fileWidth;
	rect.Bottom = (yPos + m_spriteHeight) / m_fileHeight;

	return rect;
}