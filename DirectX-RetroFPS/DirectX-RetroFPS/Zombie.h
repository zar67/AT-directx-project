#pragma once

#include "Enemy.h"

class Zombie : public Enemy
{
public:
	Zombie(Graphics& graphics, Player& player);

	void InitialiseStats() override;
};