#pragma once

#include <string>
#include <vector>

#include "Bindable.h"
#include "TextureCoordinate.h"

class SpriteSheet : public Bindable
{
public:
	struct SpriteBounds
	{
		double Left;
		double Right;
		double Top;
		double Bottom;
	};
public:
	SpriteSheet(Graphics& graphics, std::string fileName, int columnCount, int rowCount);
	~SpriteSheet() = default;

	virtual void Bind(Graphics& graphics) override;

	void SetCoordsToSpriteAt(int index, std::vector<TextureCoordinate>& textureCoords);
	SpriteBounds GetSpriteBoundsAtIndex(int index);

private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pTextureView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pTexture2D = nullptr;

	int m_columnCount = 0;
	int m_rowCount = 0;

	float m_spriteWidth = 0;
	float m_spriteHeight = 0;

	float m_fileWidth = 0;
	float m_fileHeight = 0;
};