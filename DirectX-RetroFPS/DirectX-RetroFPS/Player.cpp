#include "Player.h"
#include "SoundManager.h"

Player::Player(Input& input, float windowWidth, float windowHeight, float movementSpeed, float rotationSpeed, DirectX::XMFLOAT2 deadZoneSize)
{
	m_pInput = &input;
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;

	m_movementSpeed = movementSpeed;
	m_rotationSpeed = rotationSpeed;
	m_deadZoneSize = deadZoneSize;

	m_transform.Position.Set(0.0f, 0.0f, 0.0f);
	m_transform.Rotation.Set(0.0f, 0.0f, 0.0f);

	m_transform.ApplyScalar(0.75f, 0.75f, 0.75f);

	m_transform.ConstrainYPosition = true;

	InitialiseCollider();

	m_shooter.SetParent(this);

	m_health.SetMaxValue(100.0f);
	m_health.SetToMaxValue();

	m_armor.SetMaxValue(100.0f);

	m_weapons[WeaponType::FIST] = std::make_unique<Weapon>(WeaponType::FIST, 2.0f, 0, 0.2f, 4.0f, true);
	m_weapons[WeaponType::CHAINSAW] = std::make_unique<Weapon>(WeaponType::CHAINSAW, 5.0f, 0, 0.5f, 4.0f, true);
	m_weapons[WeaponType::PISTOL] = std::make_unique<Weapon>(WeaponType::PISTOL, 10.0f, 10, 0.5f, 15.0f, false);
	m_weapons[WeaponType::RIFLE] = std::make_unique<Weapon>(WeaponType::RIFLE, 15.0f, 20, 0.2f, 15.0f, false);
	m_weapons[WeaponType::SHOTGUN] = std::make_unique<Weapon>(WeaponType::SHOTGUN, 20.0f, 5, 1.0f, 8.0f, false);
	m_weapons[WeaponType::CANNON] = std::make_unique<Weapon>(WeaponType::CANNON, 25.0f, 1, 2.0f, 8.0f, false);

	m_shooter.SetWeapon(m_weapons[WeaponType::FIST].get());
}

void Player::Update(float deltaTime)
{
	UpdateMovement(deltaTime);
	UpdateRotation(deltaTime);
	ClampRotation();

	UpdateShooting(deltaTime);

	if (m_isDelayingHit)
	{
		m_hitTimer += deltaTime;

		if (m_hitTimer >= m_hitDelay)
		{
			m_hitTimer = 0;
			m_isDelayingHit = false;
		}
	}
}

OBBCollider& Player::GetCollider()
{
	return m_collider;
}

Shooter& Player::GetShooter()
{
	return m_shooter;
}

Stat& Player::GetHealth()
{
	return m_health;
}

Stat& Player::GetArmor()
{
	return m_armor;
}

void Player::HandleDamaged(float value)
{
	if (m_isDelayingHit)
	{
		return;
	}

	if (m_armor.GetCurrentValue() > value / 2)
	{
		m_armor.Decrease(value / 2);
		m_health.Decrease(value / 2);
	}
	else
	{
		m_health.Decrease(value);
	}

	if (m_health.IsZero())
	{
		SoundManager::GetInstance().Play(SoundType::PLAYER_DEATH);
	}
	else
	{
		SoundManager::GetInstance().Play(SoundType::PLAYER_INJURED);
	}

	m_isDelayingHit = true;
}

void Player::Reset()
{
	m_health.SetToMaxValue();
	m_armor.Set(0);
	m_hasKey = false;
}

Weapon* Player::GetWeaponOfType(WeaponType type)
{
	return m_weapons[type].get();
}

void Player::HasKey(bool key)
{
	m_hasKey = key;
};

bool Player::HasKey()
{
	return m_hasKey;
}

void Player::LockYPosition(float y)
{
	m_transform.ConstrainYPosition = false;
	m_yLockPosition = y;
	m_transform.ConstrainYPosition = true;
}

void Player::InitialiseCollider()
{
	m_collider.SetTransform(&m_transform);
	m_collider.SetRotationConstraints(true, true, true);

	m_collider.SetColliderData(Vector(-1.0f, -1.0f, -1.0f), Vector(1.0f, 1.0f, 1.0f));
}

void Player::UpdateMovement(float deltaTime)
{
	float forwardMovement = m_pInput->GetKeyboard().IsKeyDown('W') ? m_movementSpeed : 0.0f;
	float backwardMovement = m_pInput->GetKeyboard().IsKeyDown('S') ? -m_movementSpeed : 0.0f;
	float leftMovement = m_pInput->GetKeyboard().IsKeyDown('A') ? -m_movementSpeed : 0.0f;
	float rightMovement = m_pInput->GetKeyboard().IsKeyDown('D') ? m_movementSpeed : 0.0f;

	float xMovement = (leftMovement + rightMovement) * deltaTime;
	float zMovement = (forwardMovement + backwardMovement) * deltaTime;

	Vector translation = m_transform.ApplyTranslation(xMovement, 0.0f, zMovement);
	m_collider.IncreaseVelocity(translation);
}

void Player::UpdateRotation(float deltaTime)
{
	while (const auto delta = m_pInput->GetMouse().ReadRawDelta())
	{
		float verticalRotation = delta->X * deltaTime * m_rotationSpeed;
		float horizontalRotation = delta->Y * deltaTime * m_rotationSpeed;
		m_transform.ApplyRotation(horizontalRotation, verticalRotation, 0.0f);
	}
}

void Player::ClampRotation()
{
	if (m_transform.Rotation.X > DirectX::XMConvertToRadians(LOOK_Y_CLAMP))
	{
		m_transform.Rotation.X = DirectX::XMConvertToRadians(LOOK_Y_CLAMP);
	}
	else if (m_transform.Rotation.X < DirectX::XMConvertToRadians(-LOOK_Y_CLAMP))
	{
		m_transform.Rotation.X = DirectX::XMConvertToRadians(-LOOK_Y_CLAMP);
	}
}

void Player::UpdateShooting(float deltaTime)
{
	bool shoot = m_pInput->GetMouse().GetLeftButtonState() == MouseEvent::ButtonState::PRESSED;
	m_shooter.ClearShooter();

	if (shoot && m_shooter.CanShoot())
	{
		DirectX::XMMATRIX cameraRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(m_transform.Rotation.X, m_transform.Rotation.Y, m_transform.Rotation.Z);
		DirectX::XMVECTOR cameraTarget = DirectX::XMVector3TransformCoord(DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f), cameraRotationMatrix);
		DirectX::XMFLOAT3 cameraForwardVector;
		DirectX::XMStoreFloat3(&cameraForwardVector, cameraTarget);

		Vector rayDirection = Vector(cameraForwardVector);
		rayDirection = rayDirection.GetNormalized();

		if (!m_shooter.IsShooting())
		{
			m_shooter.StartShoot(Ray(m_transform.Position, rayDirection));
		}
	}

	for (auto& weapon : m_weapons)
	{
		weapon.second->Update(deltaTime);
	}

	if (m_pInput->GetKeyboard().IsKeyDown('1'))
	{
		m_shooter.SetWeapon(m_weapons[WeaponType::FIST].get());
	}
	else if (m_pInput->GetKeyboard().IsKeyDown('2'))
	{
		m_shooter.SetWeapon(m_weapons[WeaponType::CHAINSAW].get());
		SoundManager::GetInstance().Play(SoundType::CHAINSAW_IDLE);
	}
	else if (m_pInput->GetKeyboard().IsKeyDown('3'))
	{
		m_shooter.SetWeapon(m_weapons[WeaponType::PISTOL].get());
	}
	else if (m_pInput->GetKeyboard().IsKeyDown('4'))
	{
		m_shooter.SetWeapon(m_weapons[WeaponType::RIFLE].get());
	}
	else if (m_pInput->GetKeyboard().IsKeyDown('5'))
	{
		m_shooter.SetWeapon(m_weapons[WeaponType::SHOTGUN].get());
	}
	else if (m_pInput->GetKeyboard().IsKeyDown('6'))
	{
		m_shooter.SetWeapon(m_weapons[WeaponType::CANNON].get());
	}
}