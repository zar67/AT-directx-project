#pragma once
#include "Drawable.h"

class TexturedCube : public Drawable<TexturedCube>
{
public:
	TexturedCube(Graphics& graphics, float pitchRotateSpeed, float yawRotateSpeed, float rollRotateSpeed);

	virtual void Update(float deltaTime) override;
private:
	void InitialiseStatic(Graphics& graphics);
	void InitialiseCollider();

	float m_pitchRotateSpeed;
	float m_yawRotateSpeed;
	float m_rollRotateSpeed;
};