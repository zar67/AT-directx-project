#pragma once
#include "Bindable.h"

class TextureBindable : public Bindable
{
public:
	TextureBindable(Graphics& graphics, std::string filename);
	virtual ~TextureBindable() = default;

	virtual void Bind(Graphics& graphics) override;
protected:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pTextureView = nullptr;
};