#pragma once
#include "Drawable.h"

class Enemy : public Drawable<Enemy>
{
public:
	Enemy() = default;
	Enemy(Graphics & graphics);

	virtual void Update(float deltaTime) override;
private:
	void InitialiseStatic(Graphics & graphics);
};