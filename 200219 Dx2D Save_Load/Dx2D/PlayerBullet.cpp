#include "stdafx.h"
#include "PlayerBullet.h"


PlayerBullet::PlayerBullet()
{
	m_pCircle = new Circle;
	m_pCircle->SetRadius(10);
}


PlayerBullet::~PlayerBullet()
{
	SAFE_DELETE(m_pCircle);
}

void PlayerBullet::Init()
{
	m_vecBullet.clear();
}

void PlayerBullet::Update()
{
	for (int i = m_vecBullet.size() - 1; i >= 0; i--)
	{
		switch (m_vecBullet[i].type)
		{
		case BTYPE::SPEED:
			m_vecBullet[i].pos += m_vecBullet[i].dest * m_vecBullet[i].speed * g_pTimeManager->GetDeltaTime();
			break;
		case BTYPE::INTERPOLATION:
			m_vecBullet[i].elapsedTime += g_pTimeManager->GetDeltaTime();

			m_vecBullet[i].pos = LinearInterpolation(m_vecBullet[i].start, m_vecBullet[i].dest,
				m_vecBullet[i].elapsedTime / m_vecBullet[i].time);
			break;
		case BTYPE::BEZIER:
			m_vecBullet[i].elapsedTime += g_pTimeManager->GetDeltaTime();
			
			m_vecBullet[i].pos = BezierCurve(m_vecBullet[i].start,
				m_vecBullet[i].via, m_vecBullet[i].dest,
				m_vecBullet[i].elapsedTime / m_vecBullet[i].time);
			break;
		}
	}
}

void PlayerBullet::Render()
{
	for (int i = 0; i < m_vecBullet.size(); i++)
	{
		m_pCircle->SetPosition(m_vecBullet[i].pos);
		m_pCircle->Update();
		m_pCircle->Render();
	}
}

void PlayerBullet::ShootBullet(D3DXVECTOR2 start, float f, BTYPE type)
{
	tagBullet bullet;
	bullet.type = type;

	switch (bullet.type)
	{
	case BTYPE::SPEED:
		bullet.pos = start;
		bullet.dest = D3DXVECTOR2(g_ptMouse.x, g_ptMouse.y) - start; // direction
		D3DXVec2Normalize(&bullet.dest, &bullet.dest);
		bullet.speed = f;
		break;
	case BTYPE::INTERPOLATION: case BTYPE::BEZIER:
		bullet.start = start;
		bullet.dest = D3DXVECTOR2(g_ptMouse.x, g_ptMouse.y);
		bullet.time = f;
		bullet.elapsedTime = 0.0f;

		//int range = (bullet.dest.x - bullet.start.x) * 2.0f;
		//bullet.via.x = (range >= 0) ? bullet.start.x + rand() % range : bullet.start.x - rand() % range;
		//
		//range = (bullet.dest.y - bullet.start.y) * 2.0f;
		//bullet.via.y = (range >= 0) ? bullet.start.y + rand() % range : bullet.start.y - rand() % range;

		int rnd = rand() % 2;

		if (rnd == 0)
		{
			bullet.via.x = bullet.start.x;
			bullet.via.y = bullet.dest.y;
		}
		else
		{
			bullet.via.x = bullet.dest.x;
			bullet.via.y = bullet.start.y;
		}
		break;
	}

	m_vecBullet.push_back(bullet);
}
