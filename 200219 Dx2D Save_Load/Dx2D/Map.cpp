#include "stdafx.h"
#include "Map.h"
#include "Player.h"


Map::Map()
	: m_pPlayer(NULL)
{
	g_pTextureManager->AddTexture(L"Back00", L"Background00.png");
	g_pTextureManager->AddTexture(L"Back01", L"Background01.png");
	g_pTextureManager->AddTexture(L"Back02", L"Background02.png");

	m_arrLayer[0] = new Sprite(L"Back00");
	m_arrLayer[0]->SetSize(2, 2);
	m_arrLayer[1] = new Sprite(L"Back01");
	m_arrLayer[1]->SetSize(2, 2);
	m_arrLayer[2] = new Sprite(L"Back02");
	m_arrLayer[2]->SetSize(2, 2);

	g_pSoundManager->AddSound("Back", "Angel Attack.mp3", true, true);
}


Map::~Map()
{
	for (auto p : m_arrLayer)
		SAFE_DELETE(p);
}

void Map::Init()
{
	m_fGroundY = 280;
	
	for (int i = 0; i < 3; i++)
	{
		m_arryLayerPosX[i] = 0;
	}

	m_fMapPosX = 0;
	m_fMapPosY = 0;

	g_pSoundManager->Play("Back");
}

void Map::Update()
{
	if (g_pKeyManager->isOnceKeyDown(VK_F1))
	{
		if (g_pSoundManager->IsPauseSound("Back"))
			g_pSoundManager->Resume("Back");
		else
			g_pSoundManager->Pause("Back");
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_F2))
	{
		if (g_pSoundManager->IsPlaySound("Back"))
			g_pSoundManager->Stop("Back");
		else
			g_pSoundManager->Play("Back");
	}
	else if (g_pKeyManager->isStayKeyDown(VK_F3))
		g_pSoundManager->VolumeUp("Back");
	else if (g_pKeyManager->isStayKeyDown(VK_F4))
		g_pSoundManager->VolumeDown("Back");

	if (m_pPlayer)
	{
		if (m_pPlayer->GetMoveDirX() != X_DIR::Walk)
		{
			m_arryLayerPosX[0] -= m_pPlayer->GetSpeed() * (int)m_pPlayer->GetMoveDirX() * g_pTimeManager->GetDeltaTime() * 0.25f;
			m_arryLayerPosX[1] -= m_pPlayer->GetSpeed() * (int)m_pPlayer->GetMoveDirX() * g_pTimeManager->GetDeltaTime() * 0.5f;
			m_arryLayerPosX[2] -= m_pPlayer->GetSpeed() * (int)m_pPlayer->GetMoveDirX() * g_pTimeManager->GetDeltaTime();

			m_fMapPosX += m_pPlayer->GetSpeed() * (int)m_pPlayer->GetMoveDirX() * g_pTimeManager->GetDeltaTime();
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (m_arryLayerPosX[i] < -m_arrLayer[i]->GetWidth())
			m_arryLayerPosX[i] = 0;
		else if (m_arryLayerPosX[i] > 0)
			m_arryLayerPosX[i] = -m_arrLayer[i]->GetWidth();
	}

	m_fMapPosY = m_pPlayer->GetMoveY();
}

void Map::Render()
{
	for (int i = 0; i < 3; i++)
	{
		m_arrLayer[i]->SetLBPosition(m_arryLayerPosX[i], -m_fMapPosY);
		m_arrLayer[i]->Update();
		m_arrLayer[i]->Render();

		if (m_arryLayerPosX[i] < -m_arrLayer[i]->GetWidth() + WINSIZEX)
		{
			m_arrLayer[i]->SetLBPosition(m_arryLayerPosX[i] + m_arrLayer[i]->GetWidth(), -m_fMapPosY);
			m_arrLayer[i]->Update();
			m_arrLayer[i]->Render();
		}
	}
}