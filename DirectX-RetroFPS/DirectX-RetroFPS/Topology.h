#pragma once
#include "Bindable.h"

class Topology : public Bindable
{
public:
	Topology(Graphics& graphics, D3D11_PRIMITIVE_TOPOLOGY topologyType);
	virtual ~Topology() = default;

	virtual void Bind(Graphics & graphics) override;
private:
	D3D11_PRIMITIVE_TOPOLOGY m_topologyType;
};