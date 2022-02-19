#pragma once

#include "Enemy.h"

class DemonPuppy : public Enemy
{
public:
	DemonPuppy(Graphics& graphics, Player& player);

	virtual void PlaySightSound() override;
	virtual void PlayInjuredSound() override;
	virtual void PlayDeathSound() override;
};