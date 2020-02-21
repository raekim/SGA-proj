#pragma once

class Map;
class Player;

struct tagObject
{
	Sprite* pSprite;
	D3DXVECTOR2 vPos;
	RECT stRect;
};

enum class MONSTATE
{
	READY = -1,
	LEFT,
	RIGHT,
	DIE,
	MAX
};

struct tagMonster
{
	Animation<MONSTATE>* pAnim;
	D3DXVECTOR2 vPos;
	RECT stRect;
	MONSTATE eState;
	float fMoveSpeed;
	float fMoveCount;
};

class MapObject
{
private:
	Map*				m_pMap;
	vector<tagObject>	m_vecObject;
	vector<tagMonster>	m_vecMonster;

	Player*				m_pPlayer;

public:
	MapObject();
	~MapObject();

	void Init();
	void Update();
	void Render();

	void SetMap(Map* p) { m_pMap = p; }
	void SetPlayer(Player* p) { m_pPlayer = p; }

	const vector<tagObject>& GetObjects() { return m_vecObject; }
};

