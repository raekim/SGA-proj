#pragma once
#include "Primitive2DObejct.h"

class Sprite : public Primitive2DObejct<PTVertex>
{
private:
	const Texture*	m_pTexture;

	float			m_fWidth;
	float			m_fHeight;

private:
	void InitSprite(wstring key, float u1, float v1, float u2, float v2, int numX = 1, int numY = 1);

public:
	Sprite(wstring key, float u1 = 0.0f, float v1 = 0.0f, float u2 = 1.0f, float v2 = 1.0f);
	Sprite(wstring key, int numX, int numY, int index);

	virtual ~Sprite() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void SetConstantScale(float x, float y);
	void SetConstantScale(D3DXVECTOR2 s);

	float GetWidth() { return m_fWidth * m_vSize.x; }
	float GetHeight() { return m_fHeight * m_vSize.y; }

	virtual void SetLBPosition(float x, float y) override;
	void SetLBPosition(D3DXVECTOR2 v);
};

