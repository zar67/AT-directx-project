#pragma once

#include "Enemy.h"

class Zombie : public Enemy
{
public:
	Zombie(Graphics& graphics, Player& player);
protected:
	const EnemyStats ENEMY_STATS = EnemyStats(100.0f);
};