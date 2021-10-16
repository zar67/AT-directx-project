#include "Box.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "VertexBuffer.h"
#include "InputLayout.h"
#include "Vertex.h"

Box::Box(Graphics& graphics)
{
	std::vector<Vertex> vertices
	{
		Vertex(0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f),
		Vertex(0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f),
		Vertex(-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f),
		Vertex(-0.3f, 0.3f, 1.0f, 0.0f, 1.0f, 0.0f),
		Vertex(0.3f, 0.3f, 1.0f, 0.0f, 0.0f, 1.0f),
		Vertex(0.0f, -0.8f, 1.0f, 0.0f, 1.0f, 0.0f)
	};

	// Create Index Buffer
	const std::vector<unsigned short> indices =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 1,
		2, 1, 5
	};

	AddBindable(std::make_unique<VertexBuffer>(graphics, vertices));

	auto pvs = std::make_unique<VertexShader>(graphics, graphics.GetShaderFolder() + L"VertexShader.cso");
	auto pvsbc = pvs->GetByteCode();
	AddBindable(std::move(pvs));

	AddBindable(std::make_unique<PixelShader>(graphics, graphics.GetShaderFolder() + L"PixelShader.cso"));
	AddIndexBuffer(std::make_unique<IndexBuffer>(graphics, indices));

	std::vector<D3D11_INPUT_ELEMENT_DESC> layout
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOUR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	AddBindable(std::make_unique<InputLayout>(graphics, layout, pvsbc));
}
