#pragma once
#include "iGameNode.h"
#include "Player.h"
#include "Map.h"
#include "MapObject.h"


class MainGame : public iGameNode
{
private:
	ID3D11Buffer* m_pViewProjBuffer;	// ��, �������� ��Ʈ���� ����
	void SetViewProjectionMatrixes();	// ��, �������� ��Ʈ���� ���� �� ���� ����

	ID3D11BlendState*	m_pNormalBlendState;	// �⺻ ���� �ɼ�
	ID3D11BlendState*	m_pAlphaBlendState;		// ������ ���� �ɼ�
	void SetBlendStates();	// �ɼǺ� ���� ���°� ����

private:
	Player*			m_pPlayer;
	Map*			m_pMap;
	MapObject*		m_pMapObject;

	Rect*			m_pRect;

public:
	MainGame();
	~MainGame();

	void CreateGameClasses();
	void DeleteGameClasses();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

