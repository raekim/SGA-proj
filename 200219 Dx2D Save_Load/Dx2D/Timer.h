#pragma once
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
// timeGetTime 함수를 사용하기 위한 라이브러리

class Timer
{
private:
	bool			m_isHardware;		// 고성능 타이머 지원여부
	float			m_fTimeScale;		// 초당 시간 계산 범위
	float			m_fDeltaTime;		// 한 프레임 당 경과 시간 (1 / 프레임)
	__int64			m_nCurrTime;		// 현재 카운트 시간
	__int64			m_nLastTime;		// 마지막 카운트 시간

	unsigned int	m_nFrameRate;		// FPS (Frame Per Second)
	unsigned int	m_nFPSFrameCount;	// FPS 카운터
	float			m_fElapsedTime;		// 경과 시간
	float			m_fWorldTime;		// 프로그램 실행 후 총 경과 시간

public:
	Timer();
	~Timer();

	void InitTimer();					// 타이머 초기화
	void Update(float lockFPS = 0.0f);	// 업데이트 (FPS 제한 값, 0 = 제한 없음)

	unsigned int GetFPS() const { return m_nFrameRate; }
	float GetDeltaTime() const { return m_fDeltaTime; }
	float GetWorldTime() const { return m_fWorldTime; }

	float GetTimeScale() { return m_fTimeScale; }
	void SetTimeScale(float s) { m_fTimeScale = s; }
};

