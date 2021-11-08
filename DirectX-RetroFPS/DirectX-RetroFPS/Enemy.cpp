#include "Enemy.h"
#include "Topology.h"
#include "VertexShader.h"
#include "InputLayout.h"
#include "RasterizerState.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "TextureBindable.h"
#include "TransformConstantBuffer.h"
#include "BlendState.h"

Enemy::Enemy(Graphics& graphics)
{
	if (!IsStaticInitialized())
	{
		InitialiseStatic(graphics);
	}

	std::unique_ptr<VertexBuffer<Vertex>> vertexBuffer = std::make_unique<VertexBuffer<Vertex>>(graphics, m_vertices);
	m_pVertexBuffer = vertexBuffer.get();
	AddBindable(std::move(vertexBuffer));

	AddBindable(std::make_unique<TransformConstantBuffer>(graphics, *this));
	
	m_pGraphics = &graphics;

	m_pIndexBuffer = GetBindableOfType<IndexBuffer>();
	m_pSpriteSheet = GetBindableOfType<SpriteSheet>();

	m_idleAnimation = Animation(m_pSpriteSheet, { 0, 8, 16 }, 5);
}

void Enemy::Draw(Graphics& graphics)
{
	m_pVertexBuffer->Update(graphics, m_vertices);

	Drawable::Draw(graphics);
}

void Enemy::Update(float deltaTime)
{
	Vector cameraForwardVector = Vector(0.0f, 0.0f, -1.0f);
	Transform& cameraTransform = m_pGraphics->GetCamera()->GetTransform();

	Vector tocameraVector = cameraTransform.Position - m_transform.Position;
	tocameraVector.Y = 0;

	float dotProduct = Vector::DotProduct(cameraForwardVector, tocameraVector);
	float radianAngle = acos(dotProduct / (cameraForwardVector.GetMagnitude() * tocameraVector.GetMagnitude()));

	if (tocameraVector.X > 0)
	{
		radianAngle = (2 * DirectX::XM_PI) - radianAngle;
	}

	m_transform.Rotation.Y = radianAngle;

	m_idleAnimation.Update(deltaTime, m_textureCoords);
	for (int i = 0; i < 4; i++)
	{
		m_vertices[i].TextureCoords = m_textureCoords[i];
	}
}

void Enemy::InitialiseStatic(Graphics& graphics)
{
	// Create Index Buffer
	const std::vector<unsigned short> indices =
	{
		0,1,3,
		1,2,3
	};

	AddStaticBindable(std::make_unique<IndexBuffer>(graphics, indices));

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

	AddStaticBindable(std::make_unique<SpriteSheet>(graphics, "Assets\\Characters\\doom_demon.png", 32, 5));

	AddStaticBindable(std::make_unique<BlendState>(graphics, true));
}