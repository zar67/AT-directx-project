#include "TexturedCube.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "VertexBuffer.h"
#include "InputLayout.h"
#include "TransformConstantBuffer.h"
#include "Sampler.h"
#include "TextureBindable.h"
#include "Topology.h"
#include "RasterizerState.h"

TexturedCube::TexturedCube(Graphics& graphics, float pitchRotateSpeed, float yawRotateSpeed, float rollRotateSpeed) :
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
	
	InitialiseCollider();
	AddBindable(std::make_unique<TransformConstantBuffer>(graphics, *this));
}

void TexturedCube::Update(float deltaTime)
{
	m_transform.ApplyRotation(m_pitchRotateSpeed * deltaTime, m_yawRotateSpeed * deltaTime, m_rollRotateSpeed * deltaTime);
}

void TexturedCube::InitialiseStatic(Graphics& graphics)
{
	struct Vertex
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT2 TextureCoords;
		DirectX::XMFLOAT3 Colour;
	};

	std::vector<Vertex> vertices
	{
		{DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(0, 1), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)}, // Front
		{DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(0.5f, 1), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(0, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(0.5f, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT3(0, 0, 1.0f), DirectX::XMFLOAT2(0.5f, 1), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)}, // Back
		{DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT3(0, 0, 1.0f), DirectX::XMFLOAT2(0, 1), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0, 0, 1.0f), DirectX::XMFLOAT2(0.5f, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0, 0, 1.0f), DirectX::XMFLOAT2(0, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(-1.0f, 0, 0), DirectX::XMFLOAT2(0.5f, 1), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)}, // Left
		{DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT3(-1.0f, 0, 0), DirectX::XMFLOAT2(0.5f, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT3(-1.0f, 0, 0), DirectX::XMFLOAT2(0, 1), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(-1.0f, 0, 0), DirectX::XMFLOAT2(0, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(1.0f, 0, 0), DirectX::XMFLOAT2(0, 1), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)}, // Right
		{DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT3(1.0f, 0, 0), DirectX::XMFLOAT2(0, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT3(1.0f, 0, 0), DirectX::XMFLOAT2(0.5f, 1), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(1.0f, 0, 0), DirectX::XMFLOAT2(0.5f, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(0, -1.0f, 0), DirectX::XMFLOAT2(0.5f, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)}, // Bottom
		{DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT3(0, -1.0f, 0), DirectX::XMFLOAT2(1, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT3(0, -1.0f, 0), DirectX::XMFLOAT2(0.5f, 1), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT3(0, -1.0f, 0), DirectX::XMFLOAT2(1, 1), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT3(0, 1.0f, 0), DirectX::XMFLOAT2(0.5f, 1), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)}, // Top
		{DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT3(0, 1.0f, 0), DirectX::XMFLOAT2(1, 1), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0, 1.0f, 0), DirectX::XMFLOAT2(0.5f, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0, 1.0f, 0), DirectX::XMFLOAT2(1, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)}
	};

	// Create Index Buffer
	const std::vector<unsigned short> indices =
	{
		0,2, 1,    2,3,1,
		4,5, 7,    4,7,6,
		8,10, 9,  10,11,9,
		12,13,15, 12,15,14,
		16,17,18, 18,17,19,
		20,23,21, 20,22,23
	};

	AddStaticBindable(std::make_unique<VertexBuffer<Vertex>>(graphics, vertices));
	AddStaticIndexBuffer(std::make_unique<IndexBuffer>(graphics, indices));

	AddStaticBindable(std::make_unique<Topology>(graphics, D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	auto vertexShader = std::make_unique<VertexShader>(graphics, graphics.GetShaderFolder() + L"TextureVS.cso");
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

	AddStaticBindable(std::make_unique<PixelShader>(graphics, graphics.GetShaderFolder() + L"TexturePS.cso"));

	AddStaticBindable(std::make_unique<Sampler>(graphics));

	AddStaticBindable(std::make_unique<TextureBindable>(graphics, "Assets\\cube.png"));
}

void TexturedCube::InitialiseCollider()
{
	m_collider.SetTransform(m_transform);
	//m_collider.SetColliderData({
	//	{DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f), DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f)}, // Left Side
	//	{DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f)}, // Right Side
	//	{DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f)}, // Front Side
	//	{DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f)}, // Back Side
	//	{DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f)}, // Top Side
	//	{DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f), DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f)} // Bottom Side
	//});
}