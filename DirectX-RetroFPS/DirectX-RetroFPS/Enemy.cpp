#include "Enemy.h"
#include "VertexBuffer.h"
#include "Topology.h"
#include "VertexShader.h"
#include "InputLayout.h"
#include "RasterizerState.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "TextureBindable.h"
#include "TransformConstantBuffer.h"

Enemy::Enemy(Graphics& graphics)
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
	
	m_pGraphics = &graphics;
}

void Enemy::Update(float deltaTime)
{
	DirectX::XMFLOAT3 cameraForwardVector = DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f);
	Transform& cameraTransform = m_pGraphics->GetCamera()->GetTransform();

	DirectX::XMFLOAT3 tocameraVector = DirectX::XMFLOAT3(
		cameraTransform.Position.x - m_transform.Position.x,
		0,
		cameraTransform.Position.z - m_transform.Position.z
	);

	float dotProduct = cameraForwardVector.x * tocameraVector.x + cameraForwardVector.y * tocameraVector.y + cameraForwardVector.z * tocameraVector.z;
	float forwardMagnitude = sqrt(pow(cameraForwardVector.x, 2) + pow(cameraForwardVector.y, 2) + pow(cameraForwardVector.z, 2));
	float toCameraMagnitude = sqrt(pow(tocameraVector.x, 2) + pow(tocameraVector.y, 2) + pow(tocameraVector.z, 2));

	float radianAngle = acos(dotProduct / (forwardMagnitude * toCameraMagnitude));

	if (tocameraVector.x > 0)
	{
		radianAngle = (2 * DirectX::XM_PI) - radianAngle;
	}

	m_transform.Rotation.y = radianAngle;
}

void Enemy::InitialiseStatic(Graphics& graphics)
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
		{DirectX::XMFLOAT3(-1.0f, -1.0f, 0.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(0, 0.2f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f, 1.0f, 0.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(0, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(0.03125f, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(1.0f, -1.0f, 0.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(0.03125f, 0.2f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
	};

	// Create Index Buffer
	const std::vector<unsigned short> indices =
	{
		0,1,3,
		1,2,3
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

	AddStaticBindable(std::make_unique<TextureBindable>(graphics, "Assets\\Characters\\doom_demon.png"));
}