#pragma once

#include "Enemy.h"

class DemonPuppy : public Enemy
{
public:
	DemonPuppy(Graphics& graphics, Player& player);

protected:
	const EnemyStats ENEMY_STATS = EnemyStats(200.0f);
};