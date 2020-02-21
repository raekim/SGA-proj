#include "stdafx.h"
#include "Timer.h"


Timer::Timer()
{
	__int64 periodFrenquency;	// 시간 업데이트 간격 초분할

	// 고성능 타이머 지원 여부 : 마이크로 세컨드 (1 / 1,000,000)
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrenquency))
	{
		m_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&m_nLastTime);

		// 초당 시간 계산 범위
		m_fTimeScale = 1.0f / periodFrenquency;
	}
	else
	{
		m_isHardware = false;
		m_nLastTime = timeGetTime();
		m_fTimeScale = 0.001f; // 밀리세컨드 (1 / 1,000)
	}

	InitTimer();
}


Timer::~Timer()
{
}

void Timer::InitTimer()
{
	if (m_isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&m_nLastTime);
	}
	else
	{
		m_nLastTime = timeGetTime();
	}

	m_nFrameRate = INT_MAX;
	m_nFPSFrameCount = 0;
	m_fElapsedTime = 0.0f;
	m_fWorldTime = 0.0f;
}

void Timer::Update(float lockFPS)
{
	if (m_isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurrTime);
	}
	else
	{
		m_nCurrTime = timeGetTime();
	}

	// 마지막 시간으로 부터 현재 시간까지의 경과 시간 (초단위)
	m_fDeltaTime = (m_nCurrTime - m_nLastTime) * m_fTimeScale;

	if (lockFPS > 0.0f)
	{
		// 프레임 제한
		while (m_fTimeScale > 0.0f && m_fDeltaTime < (1.0f / lockFPS))
		{
			if (m_isHardware)
				QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurrTime);
			else
				m_nCurrTime = timeGetTime();

			m_fDeltaTime = (m_nCurrTime - m_nLastTime) * m_fTimeScale;
		}
	}

	m_nLastTime = m_nCurrTime;
	m_nFPSFrameCount++;
	m_fElapsedTime += m_fDeltaTime;
	m_fWorldTime += m_fDeltaTime;

	if (m_fElapsedTime > 1.0f) // 1초
	{
		m_nFrameRate = m_nFPSFrameCount;
		m_nFPSFrameCount = 0;
		m_fElapsedTime = 0.0f;
	}
}
