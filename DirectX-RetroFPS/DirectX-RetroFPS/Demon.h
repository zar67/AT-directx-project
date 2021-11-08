#pragma once

#include "Enemy.h"

class Demon : public Enemy
{
public:
	Demon(Graphics& graphics);

	virtual void Update(float deltaTime) override;
};