#include "Topology.h"

Topology::Topology(Graphics& graphics, D3D11_PRIMITIVE_TOPOLOGY topologyType)
{
	m_topologyType = topologyType;
}

void Topology::Bind(Graphics& graphics)
{
	graphics.GetDeviceContext()->IASetPrimitiveTopology(m_topologyType);
}
