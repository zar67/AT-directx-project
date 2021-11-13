#pragma once

#include "Drawable.h"

class LevelExit : public Drawable<LevelExit>
{
public:
	LevelExit(Graphics& graphics);
	virtual ~LevelExit() = default;

	void Update(float deltaTime);
	void OnCollision(CollisionUtilities::ColliderCollision collision, DrawableBase* other) override;

	bool IsColliding();

private:
	void InitialiseStatic(Graphics& graphics);
	void InitialiseCollider();

	bool m_playerColliding = false;
};