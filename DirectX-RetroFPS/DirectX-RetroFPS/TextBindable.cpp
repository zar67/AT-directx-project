#include "TextBindable.h"

#include "StringConversion.h"

TextBindable::TextBindable(Graphics& graphics, std::string fontFilename)
{
	m_pSpriteBatch = std::make_unique<DirectX::SpriteBatch>(graphics.GetDeviceContext());
	m_pSpriteFont = std::make_unique<DirectX::SpriteFont>(graphics.GetDevice(), StringConversion::StringToWide(fontFilename).c_str());
}

void TextBindable::SetText(std::string text)
{
	m_text = text;
}

void TextBindable::SetTransform(Transform& transform)
{
	m_pTransform = &transform;
}

void TextBindable::SetColour(float r, float g, float b, float a)
{
	m_colour = DirectX::XMFLOAT4(r, g, b, a);
}

void TextBindable::Draw(Graphics& graphics)
{
	m_pSpriteBatch->Begin();
	m_pSpriteFont->DrawString(
		m_pSpriteBatch.get(), 
		m_text.c_str(), 
		m_pTransform->Position.AsXMVector(),
		DirectX::XMLoadFloat4(&m_colour),
		m_pTransform->Rotation.Z,
		Vector(0.0f, 0.0f, 0.0f).AsXMVector(),
		m_pTransform->Scale.AsXMVector()
	);
	m_pSpriteBatch->End();
}