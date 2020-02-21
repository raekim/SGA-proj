#include "stdafx.h"
#include "MapObject.h"
#include "Map.h"
#include "Player.h"


MapObject::MapObject()
{
	//g_pTextureManager->AddTexture(L"Bush", L"BushMario.png");
	g_pTextureManager->AddTexture(L"Bush", L"Wall1.png");

	tagObject stObject;

	for (int i = 0; i < 6; i++)
	{
		stObject.pSprite = new Sprite(L"Bush");
		stObject.pSprite->SetConstantScale(200, 50);
		stObject.vPos = D3DXVECTOR2(500 + i * 300, 430 + i * 150);
		m_vecObject.push_back(stObject);
	}

	g_pTextureManager->AddTexture(L"Monster1", L"Peon_Run.png");

	for (int i = 0; i < 5; i++)
	{
		tagMonster stMonster;

		stMonster.pAnim = new Animation<MONSTATE>();

		Clip* pClip;
		
		pClip = new Clip;
		for (int j = 0; j < 5; j++)
		{
			Sprite* pSprite = new Sprite(L"Monster1", 5, 8, j);
			pClip->AddFrame(pSprite, 1 / 5.0f);
		}
		stMonster.pAnim->AddClip(MONSTATE::RIGHT, pClip);

		pClip = new Clip;
		for (int j = 0; j < 5; j++)
		{
			Sprite* pSprite = new Sprite(L"Monster1", 5, 8, 20 + j);
			pClip->AddFrame(pSprite, 1 / 5.0f);
		}
		stMonster.pAnim->AddClip(MONSTATE::LEFT, pClip);

		pClip = new Clip;
		for (int j = 0; j < 5; j++)
		{
			Sprite* pSprite = new Sprite(L"Monster1", 5, 8, 10 + j);
			pClip->AddFrame(pSprite, 1 / 5.0f);
		}
		stMonster.pAnim->AddClip(MONSTATE::DIE, pClip);

		stMonster.pAnim->SetConstantSizeScale(128, 128);

		m_vecMonster.push_back(stMonster);
	}
}


MapObject::~MapObject()
{
	for (int i = 0; i < m_vecObject.size(); i++)
		SAFE_DELETE(m_vecObject[i].pSprite);
	m_vecObject.clear();

	for (int i = 0; i < m_vecMonster.size(); i++)
		SAFE_DELETE(m_vecMonster[i].pAnim);
	m_vecMonster.clear();
}

void MapObject::Init()
{
	for (int i = 0; i < m_vecMonster.size(); i++)
	{
		m_vecMonster[i].vPos = { 300.0f + i * 400.0f, m_pMap->GetGroundY() };
		m_vecMonster[i].eState = MONSTATE::RIGHT;
		m_vecMonster[i].pAnim->Play(MONSTATE::RIGHT);
		m_vecMonster[i].fMoveSpeed = 200.0f;
		m_vecMonster[i].fMoveCount = 5.0f;
	}
}

void MapObject::Update()
{
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i].pSprite->SetPosition(m_vecObject[i].vPos.x - m_pMap->GetMapPosX(), m_vecObject[i].vPos.y - m_pMap->GetMapPosY());
		m_vecObject[i].pSprite->Update();
		
		m_vecObject[i].stRect.left = m_vecObject[i].pSprite->GetPosition().x - m_vecObject[i].pSprite->GetWidth() * 0.5f;
		m_vecObject[i].stRect.right = m_vecObject[i].stRect.left + m_vecObject[i].pSprite->GetWidth();
		m_vecObject[i].stRect.top = m_vecObject[i].pSprite->GetPosition().y + m_vecObject[i].pSprite->GetHeight() * 0.5f;
		m_vecObject[i].stRect.bottom = m_vecObject[i].stRect.top - m_vecObject[i].pSprite->GetHeight();
	}

	for (int i = m_vecMonster.size() - 1; i >= 0; i--)
	{
		if (m_vecMonster[i].eState == MONSTATE::RIGHT)
			m_vecMonster[i].vPos.x += m_vecMonster[i].fMoveSpeed * g_pTimeManager->GetDeltaTime();
		else if (m_vecMonster[i].eState == MONSTATE::LEFT)
			m_vecMonster[i].vPos.x -= m_vecMonster[i].fMoveSpeed * g_pTimeManager->GetDeltaTime();
		else if (m_vecMonster[i].eState == MONSTATE::DIE)
		{
			m_vecMonster[i].vPos.y += 100.0f * g_pTimeManager->GetDeltaTime();

			if (m_vecMonster[i].vPos.y > WINSIZEY * 2.0f)
			{
				SAFE_DELETE(m_vecMonster[i].pAnim);
				m_vecMonster.erase(m_vecMonster.begin() + i);
				continue;
			}
		}


		if (m_vecMonster[i].fMoveCount > 0.0f)
			m_vecMonster[i].fMoveCount -= g_pTimeManager->GetDeltaTime();
		else if (m_vecMonster[i].eState != MONSTATE::DIE)
		{
			m_vecMonster[i].eState = (m_vecMonster[i].eState == MONSTATE::RIGHT) ? MONSTATE::LEFT : MONSTATE::RIGHT;
			m_vecMonster[i].pAnim->Play(m_vecMonster[i].eState);
			m_vecMonster[i].fMoveCount = 3.0f + rand() % 6;
		}

		m_vecMonster[i].pAnim->SetLBPosition(m_vecMonster[i].vPos.x - m_pMap->GetMapPosX(), m_vecMonster[i].vPos.y - m_pMap->GetMapPosY());
		m_vecMonster[i].pAnim->Update();

		m_vecMonster[i].stRect.left = m_vecMonster[i].vPos.x - m_pMap->GetMapPosX();
		m_vecMonster[i].stRect.right = m_vecMonster[i].vPos.x - m_pMap->GetMapPosX() + m_vecMonster[i].pAnim->GetWidth();
		m_vecMonster[i].stRect.top = m_vecMonster[i].vPos.y - m_pMap->GetMapPosY() + m_vecMonster[i].pAnim->GetHeight();
		m_vecMonster[i].stRect.bottom = m_vecMonster[i].vPos.y - m_pMap->GetMapPosY();

		if (m_vecMonster[i].eState != MONSTATE::DIE && AABB2D(m_pPlayer->GetRect(), m_vecMonster[i].stRect))
		{
			if (m_pPlayer->GetPosition().y > m_vecMonster[i].vPos.y - m_pMap->GetMapPosY() + 108.0f)
			{
				m_vecMonster[i].eState = MONSTATE::DIE;
				m_vecMonster[i].pAnim->Play(MONSTATE::DIE);
			}
		}
	}
}

void MapObject::Render()
{
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		m_vecObject[i].pSprite->Render();
	}

	for (int i = 0; i < m_vecMonster.size(); i++)
	{
		m_vecMonster[i].pAnim->Render();
	}
}

void MapObject::SetMonster(int idx, tagMonster m)
{
	if (idx < m_vecMonster.size()) m_vecMonster[idx] = m;
	m_vecMonster[idx].pAnim->Play(m_vecMonster[idx].eState);
}
