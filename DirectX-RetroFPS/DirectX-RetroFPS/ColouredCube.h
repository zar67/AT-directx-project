#pragma once
#include "Drawable.h"

class ColouredCube : public Drawable<ColouredCube>
{
public:
	ColouredCube() = default;
	ColouredCube(Graphics& graphics, float pitchRotateSpeed, float yawRotateSpeed, float rollRotateSpeed);

	virtual void Update(float deltaTime) override;
private:
	void InitialiseStatic(Graphics& graphics);

	float m_pitchRotateSpeed;
	float m_yawRotateSpeed;
	float m_rollRotateSpeed;
};