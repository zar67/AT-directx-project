#include "RotatingBox.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "VertexBuffer.h"
#include "InputLayout.h"
#include "Vertex.h"
#include "TransformConstantBuffer.h"
#include "Sampler.h"
#include "TextureBindable.h"

RotatingBox::RotatingBox(Graphics& graphics, float pitchRotateSpeed, float yawRotateSpeed, float rollRotateSpeed) :
	m_pitchRotateSpeed(pitchRotateSpeed),
	m_yawRotateSpeed(yawRotateSpeed),
	m_rollRotateSpeed(rollRotateSpeed)
{
	if (IsStaticInitialized())
	{
		SetIndexFromStatic();
	}
	else
	{ 
		InitialiseStatic(graphics);
	}

	AddBindable(std::make_unique<TransformConstantBuffer>(graphics, *this));
}

void RotatingBox::Update(float deltaTime)
{
	m_transform.Rotation.Pitch += m_pitchRotateSpeed * deltaTime;
	m_transform.Rotation.Yaw += m_yawRotateSpeed * deltaTime;
	m_transform.Rotation.Roll += m_rollRotateSpeed * deltaTime;
}

void RotatingBox::InitialiseStatic(Graphics& graphics)
{
	std::vector<Vertex> vertices
	{
		Vertex(DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(0, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)),
		Vertex(DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(1, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)),
		Vertex(DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(0, 1), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)),
		Vertex(DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(1, 1), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)),
		Vertex(DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(1, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)),
		Vertex(DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(0, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)),
		Vertex(DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1, 1), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)),
		Vertex(DirectX::XMFLOAT3(1.0, 1.0f, 1.0f), DirectX::XMFLOAT2(0, 1), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f))
	};

	// Create Index Buffer
	const std::vector<unsigned short> indices =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};

	AddStaticBindable(std::make_unique<VertexBuffer>(graphics, vertices));

	auto pvs = std::make_unique<VertexShader>(graphics, graphics.GetShaderFolder() + L"VertexShader.cso");
	auto pvsbc = pvs->GetByteCode();
	AddStaticBindable(std::move(pvs));

	AddStaticBindable(std::make_unique<PixelShader>(graphics, graphics.GetShaderFolder() + L"PixelShader.cso"));
	AddStaticIndexBuffer(std::make_unique<IndexBuffer>(graphics, indices));

	std::vector<D3D11_INPUT_ELEMENT_DESC> layout
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOUR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	AddStaticBindable(std::make_unique<InputLayout>(graphics, layout, pvsbc));

	AddStaticBindable(std::make_unique<Sampler>(graphics));

	AddStaticBindable(std::make_unique<TextureBindable>(graphics, "Assets\\cube.png"));
}