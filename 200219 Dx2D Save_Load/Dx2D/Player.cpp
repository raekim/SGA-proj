#include "stdafx.h"
#include "Player.h"
#include "Map.h"
#include "MapObject.h"


Player::Player()
{
	g_pTextureManager->AddTexture(L"Player", L"Player.png");

	m_pAnimation = new Animation<STATE>;

	// ��� ���� �߰�
	Clip* clip = new Clip;
	for (int i = 0; i < 12; i++)
	{
		Sprite* sprite = new Sprite(L"Player", 13, 10, i);
		clip->AddFrame(sprite, 1 / 12.0f);
	}
	m_pAnimation->AddClip(IDLE, clip);

	// �޸��� ���� �߰�
	clip = new Clip;
	for (int i = 0; i < 8; i++)
	{
		Sprite* sprite = new Sprite(L"Player", 13, 10, 13 * 6 + i);
		clip->AddFrame(sprite, 1 / 16.0f);
	}
	m_pAnimation->AddClip(RUN, clip);

	// ���� �� ���� �߰�
	clip = new Clip;
	for (int i = 0; i < 4; i++)
	{
		Sprite* sprite = new Sprite(L"Player", 13, 10, 13 * 2 + i);
		clip->AddFrame(sprite, 1 / 4.0f);
	}
	m_pAnimation->AddClip(JUMPUP, clip);

	// ���� �ٿ� ���� �߰�
	clip = new Clip;
	for (int i = 0; i < 4; i++)
	{
		Sprite* sprite = new Sprite(L"Player", 13, 10, 13 * 4 + i);
		clip->AddFrame(sprite, 1 / 4.0f);
	}
	m_pAnimation->AddClip(JUMPDOWN, clip);

	// �״� ���� �߰�
	clip = new Clip;
	for (int i = 0; i < 13; i++)
	{
		Sprite* sprite = new Sprite(L"Player", 13, 10, 13 * 8 + i);
		clip->AddFrame(sprite, 1 / 13.0f);
	}
	m_pAnimation->AddClip(DIE, clip);

	m_pRect = new Rect;
	m_pBullet = new PlayerBullet;

	g_pTextureManager->AddTexture(L"ProgressBack", L"progressBarBack.png");
	g_pTextureManager->AddTexture(L"ProgressFront", L"progressBarFront.png");

	m_pBar = new ProgressBar(L"ProgressBack", L"ProgressFront");
}

Player::~Player()
{
	SAFE_DELETE(m_pAnimation);
	SAFE_DELETE(m_pRect);
	SAFE_DELETE(m_pBullet);
}

void Player::Init()
{
	m_eState = IDLE;
	m_pAnimation->Play(m_eState);

	m_vPosition = D3DXVECTOR2(DEFAULT_X, m_pMap->GetGroundY());
	m_vRotaion = D3DXVECTOR3(0, 0, 0);
	m_pAnimation->SetScale(0.5f, 0.5f);

	m_pRect->SetSize(m_pAnimation->GetWidth() * 0.5f, m_pAnimation->GetHeight());
	m_pRect->SetDraw(false);
	m_pRect->SetBorder(true);

	m_fSpeed = 300.0f;

	m_isOnGround = true;
	m_isJumping = false;
	m_fJumpPower = 450.0f;

	m_fLeftEnd = WINSIZEX * 0.45f;
	m_fRightEnd = WINSIZEX * 0.55f;

	m_isLeft = false;

	m_nNumJump = 0;

	m_fMoveY = 150.0f;

	SAFE_INIT(m_pBullet);

	if (m_pBar)
	{
		m_pBar->SetSize(m_pAnimation->GetWidth() * 0.5f, 30);
		m_pBar->Init();
	}
}

void Player::Update()
{
	static int currState = 0;
	static const char* szName[MAX];
	
	for (int i = 0; i < MAX; i++)
		szName[i] = new char[32];

	szName[0] = "IDLE";
	szName[1] = "RUN";
	szName[2] = "JUMP UP";
	szName[3] = "JUMP DOWN";
	szName[4] = "DIE";

	ImGui::ListBox("Animation", &currState, szName, MAX);

	ImGui::InputFloat("PlayerSpeed", &m_fSpeed);

	// ĳ���� �ٶ󺸴� ����
	if (m_vPosition.x > g_ptMouse.x)
	{
		m_isLeft = true;
		m_vRotaion.y = D3DX_PI;
	}
	else
	{
		m_isLeft = false;
		m_vRotaion.y = 0.0f;
	}

	float speedRate = 1.0f;

	if (g_pKeyManager->isStayKeyDown(VK_LSHIFT))
		speedRate = 2.0f;

	if (g_pKeyManager->isStayKeyDown('D'))
	{	
		if (m_vPosition.x < m_fRightEnd)
		{
			m_vPosition.x += m_fSpeed * speedRate * g_pTimeManager->GetDeltaTime();
			m_eMoveDirX = X_DIR::Walk;
		}
		else
		{
			m_vPosition.x = m_fRightEnd;

			if (speedRate == 1.0f)
				m_eMoveDirX = X_DIR::Right;
			else
				m_eMoveDirX = X_DIR::RightRun;
		}

		//m_vRotaion.y = 0.0f;
		//m_isLeft = false;
		currState = 1;
	}
	else if (g_pKeyManager->isStayKeyDown('A'))
	{
		if (m_vPosition.x > m_fLeftEnd)
		{
			m_vPosition.x -= m_fSpeed * speedRate * g_pTimeManager->GetDeltaTime();
			m_eMoveDirX = X_DIR::Walk;
		}
		else
		{
			m_vPosition.x = m_fLeftEnd;

			if (speedRate == 1.0f)
				m_eMoveDirX = X_DIR::Left;
			else
				m_eMoveDirX = X_DIR::LeftRun;
		}

		//m_vRotaion.y = D3DX_PI;
		//m_isLeft = true;
		currState = 1;
	}
	else
	{
		m_eMoveDirX = X_DIR::Walk;
		currState = 0;
	}

	if (g_pKeyManager->isOnceKeyDown(VK_SPACE) && m_isJumping == false)
	{
		m_isOnGround = false;
		m_isJumping = true;
		m_fElapsedGravity = 0.0f;
		m_nNumJump++;
	}

	ImGui::InputFloat("PlayerPosY", &m_vPosition.y);
	static float y;
	ImGui::InputFloat("ObjectPosY", &y);

	m_stRect.left = m_pRect->GetPosition().x - m_pRect->GetSize().x * 0.5f;
	m_stRect.right = m_stRect.left + m_pRect->GetSize().x;
	m_stRect.top = m_pRect->GetPosition().y + m_pRect->GetSize().y * 0.5f;
	m_stRect.bottom = m_stRect.top - m_pRect->GetSize().y;

	if (m_isOnGround == false)
	{
		for (int i = 0; i < m_pMapObject->GetObjects().size(); i++)
		{
			tagObject object = m_pMapObject->GetObjects()[i];

			y = m_pMapObject->GetObjects()[0].pSprite->GetPosition().y;

			if (m_fElapsedGravity >= m_fJumpPower
				&& m_vPosition.y > object.pSprite->GetPosition().y
				&& AABB2D(m_stRect, object.stRect))
			{
				m_vPosition.y = object.vPos.y + object.pSprite->GetHeight() * 0.5f - m_pMap->GetMapPosY();
				m_isJumping = false;
				m_fElapsedGravity = m_fJumpPower;
				break;
			}
			
			if (i == m_pMapObject->GetObjects().size() - 1 && m_isJumping == false)
			{
				m_isJumping = true;
			}
		}
	}

	if (m_isJumping)
	{
		float speed = (m_fJumpPower - m_fElapsedGravity) * g_pTimeManager->GetDeltaTime();
		m_fElapsedGravity += GRAVITY * g_pTimeManager->GetDeltaTime();

		if (m_fJumpPower > m_fElapsedGravity)	// ���� �ö� ��
		{
			if (m_fMoveY < WINSIZEY && m_vPosition.y >= m_pMap->GetGroundY())
				m_fMoveY += speed;
			else
				m_vPosition.y += speed;

			currState = 2;
		}
		else // �Ʒ��� ������ ��
		{
			if (m_fMoveY > 150 && m_vPosition.y <= m_pMap->GetGroundY())
				m_fMoveY += speed;
			else
				m_vPosition.y += speed;

			currState = 3;
		}

		if (m_vPosition.y <= m_pMap->GetGroundY() + 150 - m_fMoveY)
		{
			m_vPosition.y = m_pMap->GetGroundY();
			m_isJumping = false;
			m_isOnGround = true;
			m_fElapsedGravity = 0.0f;
		}
	}

	float posX = m_vPosition.x + m_pAnimation->GetWidth() * 0.25f - m_pAnimation->GetWidth() * 0.5f * m_isLeft;

	m_pAnimation->SetPosition(posX, m_vPosition.y + m_pAnimation->GetHeight() * 0.5f);

	ImGui::DragFloat("Rotation X", &m_vRotaion.x);
	ImGui::DragFloat("Rotation Y", &m_vRotaion.y);
	ImGui::DragFloat("Rotation Z", &m_vRotaion.z);

	m_pAnimation->SetRotation(m_vRotaion.x, m_vRotaion.y, m_vRotaion.z);

	m_eState = (STATE)currState;
	m_pAnimation->Play(m_eState);

	m_pAnimation->Update();

	m_pRect->SetPosition(m_vPosition.x, m_vPosition.y + m_pAnimation->GetHeight() * 0.5f);
	m_pRect->Update();

	if (g_pKeyManager->isOnceKeyDown(VK_F5)) // ���Ϸ� ���� ����
	{
		//vector<string> data;
		//char szBuf[1024];
		//
		//_itoa_s(m_vPosition.x, szBuf, 10);
		//data.push_back(string(szBuf));
		//
		//_itoa_s(m_pMap->GetMapPosX(), szBuf, 10);
		//data.push_back(string(szBuf));
		//
		//_itoa_s(m_vPosition.y, szBuf, 10);
		//data.push_back(string(szBuf));
		//
		//_itoa_s(m_fMoveY, szBuf, 10);
		//data.push_back(string(szBuf));
		//
		//g_pFileManager->TxtSave(L"PlayerPosition", data);

		g_pFileManager->AddSaveString(L"���� ����", L"���̵�", "abcde");
		g_pFileManager->AddSaveInt(L"�÷��̾�", L"PosX", m_vPosition.x);
		g_pFileManager->AddSavefloat(L"��", L"PosX", m_pMap->GetMapPosX());
		g_pFileManager->AddSavefloat(L"�÷��̾�", L"PosY", m_vPosition.y);
		g_pFileManager->AddSavefloat(L"��", L"PosY", m_fMoveY);

		g_pFileManager->IniSave(L"PlayerInfo");
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_F6)) // ���Ϸ� ���� ����
	{
		//vector<string> data;
		//
		//data = g_pFileManager->TxtLoad(L"PlayerPosition");
		//
		//m_vPosition.x = atoi(data[0].c_str());
		//m_pMap->SetMapPosX(atoi(data[1].c_str()));
		//m_vPosition.y = atoi(data[2].c_str());
		//m_fMoveY = atoi(data[3].c_str());

		wstring wstr = g_pFileManager->LoadStringData(L"PlayerInfo", L"���� ����", L"���̵�");
		int nData = g_pFileManager->LoadIntegerData(L"PlayerInfo", L"�÷��̾�", L"PosX");
		float fData = g_pFileManager->LoadfloatData(L"PlayerInfo", L"�÷��̾�", L"PosY");
	}

	if (m_pBullet && g_pKeyManager->isStayKeyDown(VK_LBUTTON))
		m_pBullet->ShootBullet(m_vPosition, 500.0f, BTYPE::SPEED);
	if (m_pBullet && g_pKeyManager->isStayKeyDown(VK_RBUTTON))
		m_pBullet->ShootBullet(m_vPosition, 1.0f, BTYPE::INTERPOLATION);
	if (m_pBullet && g_pKeyManager->isStayKeyDown(VK_MBUTTON))
		m_pBullet->ShootBullet(m_vPosition, 1.0f, BTYPE::BEZIER);

	SAFE_UPDATE(m_pBullet);
	
	static float currHp = 100;
	ImGui::SliderFloat("HP", &currHp, 0, 100);

	if (m_pBar)
	{
		m_pBar->SetProgress(100, currHp, false);

		m_pBar->SetPos(m_vPosition.x - m_pAnimation->GetWidth() * 0.25f,
			m_vPosition.y + m_pAnimation->GetHeight());
		m_pBar->Update();
	}
}

void Player::Render()
{
	SAFE_RENDER(m_pAnimation);
	SAFE_RENDER(m_pRect);
	SAFE_RENDER(m_pBar);

	g_pTextManager->IntRender(m_nNumJump, 10, WINSIZEY - 120, 50, NumberType::Blue);

	SAFE_RENDER(m_pBullet);
}
