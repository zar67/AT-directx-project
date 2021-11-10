#pragma once

#include "Enemy.h"

class Demon : public Enemy
{
public:
	Demon(Graphics& graphics, Player& player);

	virtual void Update(float deltaTime) override;
};