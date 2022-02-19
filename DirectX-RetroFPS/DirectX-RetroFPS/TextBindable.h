#pragma once

#include <SpriteBatch.h>
#include <SpriteFont.h>

#include "Bindable.h"

class TextBindable : public Bindable
{
public:
	TextBindable(Graphics& Graphics, std::string fontFilename);
	virtual ~TextBindable() = default;

	void SetText(std::string text);
	void SetTransform(Transform& transform);
	void SetColour(float r, float g, float b, float a);

	virtual void Draw(Graphics& graphics);

private:
	std::unique_ptr<DirectX::SpriteBatch> m_pSpriteBatch;
	std::unique_ptr<DirectX::SpriteFont> m_pSpriteFont;

	std::string m_text = "";
	Transform* m_pTransform = nullptr;
	DirectX::XMFLOAT4 m_colour = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
};