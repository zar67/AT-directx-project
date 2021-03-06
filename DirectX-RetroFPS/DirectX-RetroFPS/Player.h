#pragma once

#include <map>

#include "Drawable.h"
#include "Input.h"
#include "CollisionUtilities.h"
#include "Shooter.h"
#include "Stat.h"
#include "Weapon.h"

class Player : public Drawable<Player>
{
public:
	Player(Input& input, float windowWidth, float windowHeight, float movementSpeed, float rotationSpeed, DirectX::XMFLOAT2 deadZoneSize);
	~Player() = default;

	void Update(float deltaTime) override;

	OBBCollider& GetCollider();
	Shooter& GetShooter();
	Stat& GetHealth();
	Stat& GetArmor();

	void HandleDamaged(float value);
	void Reset();

	Weapon* GetWeaponOfType(WeaponType type);

	void HasKey(bool key);
	bool HasKey();
		
	void LockYPosition(float y);

private:
	void InitialiseCollider();

	void UpdateMovement(float deltaTime);
	void UpdateRotation(float deltaTime);
	void ClampRotation();

	void UpdateShooting(float deltaTime);

	Input* m_pInput = nullptr;
	float m_windowWidth;
	float m_windowHeight;

	OBBCollider m_collider;
	Shooter m_shooter;
	Stat m_health;
	Stat m_armor;

	std::map<WeaponType, std::unique_ptr<Weapon>> m_weapons;

	bool m_hasKey = false;

	float m_yLockPosition;

	float m_movementSpeed;
	float m_rotationSpeed;
	DirectX::XMFLOAT2 m_deadZoneSize;

	const float LOOK_Y_CLAMP = 45.0f;

	float m_hitTimer = 0;
	float m_hitDelay = 1;
	bool m_isDelayingHit = false;
};