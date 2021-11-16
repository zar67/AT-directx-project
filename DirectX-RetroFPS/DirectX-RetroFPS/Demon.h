#pragma once

#include "Enemy.h"
#include "Fireball.h"

class Demon : public Enemy
{
public:
	Demon(Graphics& graphics, Player& player);

	void Draw(Graphics& graphics);
	void Update(float deltaTime) override;

private:
	float m_shootDelay = 3.0f;
	float m_shootTimer = 0;

	std::vector<std::unique_ptr<Fireball>> m_fireballs;
};