#pragma once
#include "Bindable.h"

class RasterizerState : public Bindable
{
public:
	RasterizerState(Graphics& graphics);
	virtual ~RasterizerState() = default;

	virtual void Bind(Graphics & graphics);
private:
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_pRasterizerState = nullptr;
};