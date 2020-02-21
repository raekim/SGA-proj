#include "stdafx.h"
#include "Clip.h"


Clip::Clip(PlayMode mode, float speed)
	: m_ePlayMode(mode)
	, m_isPlaying(false)
	, m_nCurrFrame(0)
	, m_nStartFrame(0)
	, m_fElapsedTime(0)
	, m_fSpeed(speed)
	, m_vPosition(0, 0)
{
}


Clip::~Clip()
{
	for (Frame* p : m_vecFrame)
	{
		SAFE_DELETE(p->pSprite);
		SAFE_DELETE(p);
	}
	m_vecFrame.clear();
}

void Clip::AddFrame(Sprite * p, float t)
{
	m_vecFrame.push_back(new Frame(p, t));
}

void Clip::SetPosition(float x, float y)
{
	for (Frame* p : m_vecFrame)
		p->pSprite->SetPosition(x, y);
}

void Clip::SetPosition(D3DXVECTOR2 v)
{
	this->SetPosition(v.x, v.y);
}

void Clip::SetLBPosition(float x, float y)
{
	for (Frame* p : m_vecFrame)
		p->pSprite->SetLBPosition(x, y);
}

void Clip::SetLBPosition(D3DXVECTOR2 v)
{
	this->SetLBPosition(v.x, v.y);
}

void Clip::SetRotation(float x, float y, float z)
{
	for (Frame* p : m_vecFrame)
		p->pSprite->SetRotation(x, y, z);
}

void Clip::SetRotation(D3DXVECTOR3 r)
{
	this->SetRotation(r.x, r.y, r.z);
}

void Clip::SetScale(float x, float y)
{
	for (Frame* p : m_vecFrame)
		p->pSprite->SetSize(x, y);
}

void Clip::SetScale(D3DXVECTOR2 s)
{
	this->SetScale(s.x, s.y);
}

void Clip::SetConstantScale(float x, float y)
{
	for (Frame* p : m_vecFrame)
	{
		p->pSprite->SetConstantScale(x, y);
	}
}

void Clip::SetConstantScale(D3DXVECTOR2 s)
{
	this->SetConstantScale(s.x, s.y);
}

void Clip::Play()
{
	m_nCurrFrame = m_nStartFrame;
	m_isPlaying = true;
}

void Clip::Play(UINT startFrame)
{
	m_nStartFrame = startFrame;
	this->Play();
}

void Clip::PlayReverse()
{
	switch (m_ePlayMode)
	{
	case PlayMode::Once:
		m_ePlayMode = PlayMode::ReverseOnce;
		break;
	case PlayMode::Loop:
		m_ePlayMode = PlayMode::ReverseLoop;
		break;
	case PlayMode::ReverseOnce:
		m_ePlayMode = PlayMode::Once;
		break;
	case PlayMode::ReverseLoop:
		m_ePlayMode = PlayMode::Loop;
		break;
	}
}

void Clip::Stop()
{
	m_nCurrFrame = m_nStartFrame;
	m_isPlaying = false;
}

void Clip::Pause()
{
	m_isPlaying = false;
}

void Clip::Resume()
{
	m_isPlaying = true;
}

void Clip::Update()
{
	if (m_isPlaying)
	{
		Frame* frame = m_vecFrame[m_nCurrFrame];

		float playingTime = frame->fPlayTime * (1 / m_fSpeed);
		m_fElapsedTime += g_pTimeManager->GetDeltaTime();

		if (playingTime <= m_fElapsedTime)
		{
			switch (m_ePlayMode)
			{
			case PlayMode::Once:
				m_nCurrFrame++;
				if (m_nCurrFrame == m_vecFrame.size())
					Stop();
				break;
			case PlayMode::Loop:
				m_nCurrFrame++;
				if (m_nCurrFrame == m_vecFrame.size())
					m_nCurrFrame = m_nStartFrame;
				break;
			case PlayMode::ReverseOnce:
				m_nCurrFrame--;
				if (m_nCurrFrame < m_nStartFrame)
					Stop();
				break;
			case PlayMode::ReverseLoop:
				m_nCurrFrame--;
				if (m_nCurrFrame < m_nStartFrame)
					m_nCurrFrame = m_vecFrame.size() - 1;
				break;
			}

			m_fElapsedTime = 0.0f;
		}
	}

	m_vecFrame[m_nCurrFrame]->pSprite->Update();
}

void Clip::Render()
{
	m_vecFrame[m_nCurrFrame]->pSprite->Render();
}
