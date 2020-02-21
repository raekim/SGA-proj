#pragma once
#include "Primitive2DObejct.h"

#define NUM_SLICE 30

class Circle : public Primitive2DObejct<PCVertex>
{
private:
	float					m_fRadius;
	float					m_fSpeed;		// 이동 속도
	float					m_fAngle;		// 이동 방향

public:
	Circle();
	virtual ~Circle() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void SetRadius(float r)
	{
		m_fRadius = r;
		m_vSize.x = r * 2.0f;
		m_vSize.y = r * 2.0f;
	}

	float GetRadius() { return m_fRadius; }
	void SetSpeed(float s) { m_fSpeed = s; }
	void SetAngle(float a) { m_fAngle = a; }
};