#pragma once
#include "Bindable.h"

class Sampler : public Bindable
{
public:
	Sampler(Graphics& graphics);
	virtual ~Sampler() = default;

	virtual void Bind(Graphics& graphics) override;
protected:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_pSamplerState = nullptr;
};