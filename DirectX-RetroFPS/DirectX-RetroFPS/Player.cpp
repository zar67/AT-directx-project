#include "Player.h"

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

	m_shooter.SetDamage(10.0f);
	m_shooter.SetParent(this);

	m_health.SetMaxValue(100.0f);
	m_health.SetToMaxValue();

	m_armor.SetMaxValue(100.0f);

	m_weapons[WeaponType::FIST] = std::make_unique<Weapon>(WeaponType::FIST, 2.0f, 0, 0.2f, true);
	m_weapons[WeaponType::PISTOL] = std::make_unique<Weapon>(WeaponType::PISTOL, 10.0f, 10, 0.5f, false);
	m_weapons[WeaponType::RIFLE] = std::make_unique<Weapon>(WeaponType::RIFLE, 5.0f, 20, 0.2f, false);
	m_weapons[WeaponType::SHOTGUN] = std::make_unique<Weapon>(WeaponType::PISTOL, 20.0f, 5, 1.0f, false);
	m_weapons[WeaponType::CANNON] = std::make_unique<Weapon>(WeaponType::PISTOL, 25.0f, 1, 2.0f, false);

	m_shooter.SetWeapon(m_weapons[WeaponType::FIST].get());
}

void Player::Update(float deltaTime)
{
	UpdateMovement(deltaTime);
	UpdateRotation(deltaTime);
	ClampRotation();

	UpdateShooting(deltaTime);
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
	if (m_armor.GetCurrentValue() > value / 2)
	{
		m_armor.Decrease(value / 2);
		m_health.Decrease(value / 2);
	}
	else
	{
		m_health.Decrease(value);
	}
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
	DirectX::XMFLOAT2 windowCenter = DirectX::XMFLOAT2(m_windowWidth / 2, m_windowHeight / 2);
	DirectX::XMFLOAT2 mousePosition = DirectX::XMFLOAT2(m_pInput->GetMouse().GetXPos(), m_pInput->GetMouse().GetYPos());
	DirectX::XMFLOAT2 deadZone = DirectX::XMFLOAT2(m_windowWidth / 2 - m_deadZoneSize.x / 2, m_windowHeight / 2 - m_deadZoneSize.y / 2);

	DirectX::XMFLOAT2 mouseDirectionVector = DirectX::XMFLOAT2(mousePosition.x - windowCenter.x, mousePosition.y - windowCenter.y);
	float mouseDirectionLength = sqrt(pow(mouseDirectionVector.x, 2) + pow(mouseDirectionVector.y, 2));
	DirectX::XMFLOAT2 normalisedMouseDirection = DirectX::XMFLOAT2(mouseDirectionVector.x / mouseDirectionLength, mouseDirectionVector.y / mouseDirectionLength);

	float normalisedDirectionLengthX = abs(mouseDirectionVector.x / (m_windowWidth / 2));
	float normalisedDirectionLengthY = abs(mouseDirectionVector.y / (m_windowHeight / 2));

	float horizontalRotation = normalisedMouseDirection.x * normalisedDirectionLengthX * deltaTime * m_rotationSpeed;
	float verticalRotation = normalisedMouseDirection.y * normalisedDirectionLengthY * deltaTime * m_rotationSpeed;

	if (mousePosition.x >= deadZone.x && mousePosition.x <= deadZone.x + m_deadZoneSize.x &&
		mousePosition.y >= deadZone.y && mousePosition.y <= deadZone.y + m_deadZoneSize.y)
	{
		horizontalRotation = 0.0f;
		verticalRotation = 0.0f;
	}

	m_transform.ApplyRotation(verticalRotation, horizontalRotation, 0.0f);
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
}