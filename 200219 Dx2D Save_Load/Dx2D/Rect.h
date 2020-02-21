#pragma once
#include "Primitive2DObejct.h"


class Rect : public Primitive2DObejct<PCVertex>
{
private:
	float m_fSpeed;		// 이동 속도
	float m_fAngle;		// 이동 방향

public:
	Rect();
	virtual ~Rect() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void SetSpeed(float s) { m_fSpeed = s; }
	void SetAngle(float a) { m_fAngle = a; }
};