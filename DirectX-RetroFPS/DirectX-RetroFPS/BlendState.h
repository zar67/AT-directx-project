#pragma once
#include "Bindable.h"

class BlendState : public Bindable
{
public:
	BlendState(Graphics& graphics, bool blending);
	~BlendState() = default;

	void Bind(Graphics& graphics) override;
private:
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_pBlendState = nullptr;
	bool m_blending;
};