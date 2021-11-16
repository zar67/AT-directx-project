#pragma once

#include "Enemy.h"

class Zombie : public Enemy
{
public:
	Zombie(Graphics& graphics, Player& player);

	virtual void PlaySightSound() override;
	virtual void PlayAttackSound() override;
	virtual void PlayInjuredSound() override;
	virtual void PlayDeathSound() override;
};