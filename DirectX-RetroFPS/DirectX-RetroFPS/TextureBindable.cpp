#include "TextureBindable.h"
#include "StringConversion.h"

TextureBindable::TextureBindable(Graphics& graphics, std::string filename)
{
	auto scratchImage = LoadDataFromFile(filename);
	const DirectX::Image* image = scratchImage.GetImage(0, 0, 0);
	m_hasAlpha = !scratchImage.IsAlphaAllOpaque();

	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = image->width;
	textureDesc.Height = image->height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA tsd = {};
	tsd.pSysMem = scratchImage.GetImage(0, 0, 0)->pixels;
	tsd.SysMemPitch = image->width * sizeof(uint8_t);
	graphics.GetDevice()->CreateTexture2D(&textureDesc, &tsd, &m_pTexture);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;
	graphics.GetDevice()->CreateShaderResourceView(m_pTexture.Get(), &srvDesc, &m_pTextureView);
}

void TextureBindable::Bind(Graphics& graphics)
{
	graphics.GetDeviceContext()->PSSetShaderResources(0, 1, m_pTextureView.GetAddressOf());
}

DirectX::ScratchImage TextureBindable::LoadDataFromFile(const std::string& filename)
{
	DirectX::ScratchImage scratch;

	std::wstring wideFilename = StringConversion::StringToWide(filename);
	HRESULT hResult = DirectX::LoadFromWICFile(wideFilename.c_str(), DirectX::WIC_FLAGS_IGNORE_SRGB, nullptr, scratch);

	if (FAILED(hResult))
	{
		ErrorLogger::Log(hResult, "Failed to load image: " + filename);
	}

	if (scratch.GetImage(0, 0, 0)->format != DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM)
	{
		DirectX::ScratchImage convertedScratch;
		hResult = DirectX::Convert(
			*scratch.GetImage(0, 0, 0),
			DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM,
			DirectX::TEX_FILTER_DEFAULT,
			DirectX::TEX_THRESHOLD_DEFAULT,
			convertedScratch
		);

		if (FAILED(hResult))
		{
			ErrorLogger::Log(hResult, "Failed to convert image: " + filename);
		}

		return std::move(convertedScratch);
	}

	return std::move(scratch);
}