#include "stdafx.h"
#include "TimeManager.h"


TimeManager::TimeManager()
{
	m_pTimer = new Timer;
}


TimeManager::~TimeManager()
{
	SAFE_DELETE(m_pTimer);
}

void TimeManager::Init()
{
	m_pTimer->InitTimer();
}

void TimeManager::Update(float lock)
{
	m_pTimer->Update(lock);
}

void TimeManager::Render()
{
	float worldTime = m_pTimer->GetWorldTime();
	float FPS = m_pTimer->GetFPS();

	ImGui::InputFloat("PlayTime", &worldTime);
	ImGui::InputFloat("FPS", &FPS);
}
