#pragma once

#include "Enemy.h"

class DemonPuppy : public Enemy
{
public:
	DemonPuppy(Graphics& graphics, Player& player);

	void InitialiseStats() override;
};