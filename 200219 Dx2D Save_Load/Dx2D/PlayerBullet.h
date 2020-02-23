#pragma once

enum class BTYPE { SPEED, INTERPOLATION, BEZIER };

class PlayerBullet
{
	struct tagBullet
	{
		BTYPE		type;

		D3DXVECTOR2 start;
		D3DXVECTOR2 via;
		D3DXVECTOR2 dest;
		float elapsedTime;
		float time;

		D3DXVECTOR2 pos;
		float speed;
	};

private:
	vector<tagBullet>	m_vecBullet;
	Circle*				m_pCircle;

public:
	PlayerBullet();
	~PlayerBullet();

	void Init();
	void Update();
	void Render();

	void ShootBullet(D3DXVECTOR2 start, float f, BTYPE type);
};

