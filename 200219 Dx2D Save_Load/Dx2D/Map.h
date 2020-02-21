#pragma once

class Player;

class Map
{
private:
	Sprite*			m_arrLayer[3];
	float			m_arryLayerPosX[3];
	float			m_fGroundY;

	Player*			m_pPlayer;
	float			m_fMapPosX;
	float			m_fMapPosY;

public:
	Map();
	~Map();

	void Init();
	void Update();
	void Render();

	void SetPlayer(Player* p) { m_pPlayer = p; }

	float GetGroundY() { return m_fGroundY; }
	float GetMapPosX() { return m_fMapPosX; }
	void SetMapPosX(float f) { m_fMapPosX = f; }
	float GetMapPosY() { return m_fMapPosY; }

	void SetArryLayerPosX(float posX)
	{
		m_arryLayerPosX[0] = -posX * 0.25f;
		m_arryLayerPosX[1] = -posX * 0.5f;
		m_arryLayerPosX[2] = -posX;
	}
};

