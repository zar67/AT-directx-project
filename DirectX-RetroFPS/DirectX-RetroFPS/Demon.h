#pragma once

#include "Enemy.h"
#include "Fireball.h"

class Demon : public Enemy
{
public:
	Demon(Graphics& graphics, Player& player);

	void Draw(Graphics& graphics);
	void Update(float deltaTime) override;
	virtual void OnShot(DrawableBase* shooter, float damage, Vector shotContactPosition) override;

	void HandleFireballCollisions(DrawableBase* drawable);
	void HandlePlayerFireballCollision();

	virtual void PlaySightSound() override;
	virtual void PlayInjuredSound() override;
	virtual void PlayDeathSound() override;

private:
	float m_shootDelay = 3.0f;
	float m_shootTimer = 0;

	std::vector<std::unique_ptr<Fireball>> m_fireballs;
};