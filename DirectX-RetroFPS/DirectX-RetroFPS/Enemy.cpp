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

Enemy::Enemy(Graphics& graphics, Player& player)
{
	if (!IsStaticInitialized())
	{
		InitialiseStatic(graphics);
	}

	InitialiseCollider();

	std::unique_ptr<VertexBuffer<Vertex>> vertexBuffer = std::make_unique<VertexBuffer<Vertex>>(graphics, m_vertices);
	m_pVertexBuffer = vertexBuffer.get();
	AddBindable(std::move(vertexBuffer));

	AddBindable(std::make_unique<TransformConstantBuffer>(graphics, *this));
	
	m_pGraphics = &graphics;
	m_pPlayer = &player;

	m_pIndexBuffer = GetBindableOfType<IndexBuffer>();

	m_health.SetMaxValue(100.0f);
}

void Enemy::Draw(Graphics& graphics)
{
	if (!IsActive())
	{
		return;
	}

	m_pVertexBuffer->Update(graphics, m_vertices);

	Drawable::Draw(graphics);
}

void Enemy::Update(float deltaTime)
{
	bool previousSeenPlayer = m_seesPlayer;
	m_seesPlayer = (m_pPlayer->GetTransform().Position - m_transform.Position).GetMagnitude() < m_playerLookDistance;

	if (m_seesPlayer && !previousSeenPlayer)
	{
		PlaySightSound();
	}

	RotateToPlayer();
	UpdateFacingDirection();
	
	if (m_seesPlayer && m_movementSpeed > 0 && m_currentState != EnemyState::DEATH && m_currentState != EnemyState::HURT)
	{
		MoveToPlayer(deltaTime);
	}

	m_animationMap[m_currentState][m_currentDirection].Update(deltaTime, m_textureCoords);
	for (int i = 0; i < 4; i++)
	{
		m_vertices[i].TextureCoords = m_textureCoords[i].Coordinate;
	}

	if (m_currentState == EnemyState::DEATH &&
		m_animationMap[m_currentState][m_currentDirection].Completed())
	{
		SetActive(false);
	}

	if (m_currentState == EnemyState::ATTACKING &&
		m_animationMap[m_currentState][m_currentDirection].Completed())
	{
		ChangeState(EnemyState::IDLE);
	}

	if (m_currentState == EnemyState::HURT)
	{
		m_hurtTimer += deltaTime;
		if (m_hurtTimer >= m_hurtDelay)
		{
			ChangeState(EnemyState::IDLE);
			m_hurtTimer = 0;
		}
	}
}

void Enemy::OnShot(DrawableBase* shooter, float damage, Vector shotContactPosition)
{
	if (m_currentState != EnemyState::DEATH)
	{
		m_health.Decrease(damage);

		if (m_health.IsZero())
		{
			ChangeState(EnemyState::DEATH);
			PlayDeathSound();
		}
		else
		{
			ChangeState(EnemyState::HURT);
			PlayInjuredSound();
			m_hurtTimer = 0;
		}
	}
}

void Enemy::OnCollision(CollisionUtilities::ColliderCollision collision, DrawableBase* other)
{
	Player* player = dynamic_cast<Player*>(other);
	if (player != nullptr)
	{
		player->HandleDamaged(10.0f);
		PlayAttackSound();
		ChangeState(EnemyState::ATTACKING);
	}
}

void Enemy::ChangeState(EnemyState state)
{
	m_currentState = state;
	m_animationMap[m_currentState][m_currentDirection].Reset();
}

void Enemy::ChangeDirection(FaceDirection direction)
{
	Animation& previousAnimation = m_animationMap[m_currentState][m_currentDirection];

	m_currentDirection = direction;
	m_animationMap[m_currentState][m_currentDirection].Reset(previousAnimation.GetCurrentSpriteIndex(), previousAnimation.GetCurrentAnimationTimer());
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

	AddStaticBindable(std::make_unique<BlendState>(graphics, true));
}

void Enemy::InitialiseCollider()
{
	m_collider.SetTransform(&m_transform);
	m_collider.SetRotationConstraints(true, true, true);
	m_collider.SetColliderData(Vector(-1.0f, -1.0f, -1.0f), Vector(1.0f, 2.0f, 1.0f));
}

void Enemy::RotateToPlayer()
{
	Vector forwardVector = Vector(0.0f, 0.0f, -1.0f);
	Transform& cameraTransform = m_pPlayer->GetTransform();

	Vector toCameraVector = cameraTransform.Position - m_transform.Position;
	toCameraVector.Y = 0;

	float dotProduct = Vector::DotProduct(forwardVector, toCameraVector);
	float rotationAngle = acos(dotProduct / (forwardVector.GetMagnitude() * toCameraVector.GetMagnitude()));

	if (toCameraVector.X > 0)
	{
		rotationAngle = (2 * DirectX::XM_PI) - rotationAngle;
	}

	m_transform.Rotation.Y = rotationAngle;
}

void Enemy::UpdateFacingDirection()
{
	Transform& cameraTransform = m_pPlayer->GetTransform();

	Vector toCameraVector = cameraTransform.Position - m_transform.Position;
	toCameraVector.Y = 0;

	m_lookVector = m_seesPlayer ? toCameraVector.GetNormalized() : m_lookVector;

	float dotProduct = Vector::DotProduct(m_lookVector, toCameraVector);
	float angle = acos(dotProduct / (m_lookVector.GetMagnitude() * toCameraVector.GetMagnitude()));

	if (toCameraVector.X > 0)
	{
		angle = (2 * DirectX::XM_PI) - angle;
	}

	int directionIndex = (int)(angle / ( (2 * DirectX::XM_PI) / 8));

	if ((FaceDirection)directionIndex != m_currentDirection)
	{
		ChangeDirection((FaceDirection)directionIndex);
	}
}

void Enemy::MoveToPlayer(float deltaTime)
{
	Vector movement = (m_pPlayer->GetTransform().Position - m_transform.Position).GetNormalized();
	movement.Y = 0;
	movement *= m_movementSpeed * deltaTime;

	m_transform.ApplyTranslationOnAxes(movement);
	m_collider.IncreaseVelocity(movement);
}