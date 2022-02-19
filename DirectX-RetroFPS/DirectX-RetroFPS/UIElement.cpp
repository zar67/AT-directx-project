#include "UIElement.h"
#include "Topology.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "InputLayout.h"
#include "RasterizerState.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "TextureBindable.h"
#include "TransformConstantBuffer.h"
#include "BlendState.h"

UIElement::UIElement(Graphics& graphics)
{
	if (!IsStaticInitialized())
	{
		InitialiseStatic(graphics);
	}

	std::unique_ptr<VertexBuffer<Vertex>> vertexBuffer = std::make_unique<VertexBuffer<Vertex>>(graphics, m_vertices);
	m_pVertexBuffer = vertexBuffer.get();
	AddBindable(std::move(vertexBuffer));

	AddBindable(std::make_unique<TransformConstantBuffer>(graphics, *this));

	m_pIndexBuffer = GetBindableOfType<IndexBuffer>();
}

void UIElement::SetTargetCamera(Camera* camera)
{
	m_camera = camera;
}

void UIElement::SetOffset(Vector offset)
{
	m_offset = offset;
}

void UIElement::Update(float deltaTime)
{
	m_transform.Position = m_camera->GetTransform()->Position;
	m_transform.Rotation = m_camera->GetTransform()->Rotation + DirectX::XM_PI;
	m_transform.Rotation.X *= -1;

	m_transform.ApplyTranslation(m_offset);
}

void UIElement::InitialiseStatic(Graphics& graphics)
{
	const std::vector<unsigned short> indices =
	{
		0,1,3,
		1,2,3
	};

	AddStaticBindable(std::make_unique<IndexBuffer>(graphics, indices));

	AddStaticBindable(std::make_unique<Topology>(graphics, D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	auto vertexShader = std::make_unique<VertexShader>(graphics, graphics.GetShaderFolder() + L"UnlitTextureVS.cso");
	auto vertexShaderByteCode = vertexShader->GetByteCode();
	AddStaticBindable(std::move(vertexShader));

	std::vector<D3D11_INPUT_ELEMENT_DESC> layout
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOUR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	AddStaticBindable(std::make_unique<InputLayout>(graphics, layout, vertexShaderByteCode));

	AddStaticBindable(std::make_unique<RasterizerState>(graphics));

	AddStaticBindable(std::make_unique<PixelShader>(graphics, graphics.GetShaderFolder() + L"UnlitTexturePS.cso"));

	AddStaticBindable(std::make_unique<Sampler>(graphics));

	AddStaticBindable(std::make_unique<BlendState>(graphics, true));
}