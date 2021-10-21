#pragma once
#include "Bindable.h"
#include "DirectXTex.h"

class TextureBindable : public Bindable
{
public:
	TextureBindable(Graphics& graphics, std::string filename);
	virtual ~TextureBindable() = default;

	virtual void Bind(Graphics& graphics) override;
protected:
	DirectX::ScratchImage LoadDataFromFile(const std::string& filename);

	int m_width = 0;
	int m_height = 0;
	bool m_hasAlpha;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pTextureView = nullptr;
};