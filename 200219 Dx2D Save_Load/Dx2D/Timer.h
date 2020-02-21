#pragma once
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
// timeGetTime �Լ��� ����ϱ� ���� ���̺귯��

class Timer
{
private:
	bool			m_isHardware;		// ���� Ÿ�̸� ��������
	float			m_fTimeScale;		// �ʴ� �ð� ��� ����
	float			m_fDeltaTime;		// �� ������ �� ��� �ð� (1 / ������)
	__int64			m_nCurrTime;		// ���� ī��Ʈ �ð�
	__int64			m_nLastTime;		// ������ ī��Ʈ �ð�

	unsigned int	m_nFrameRate;		// FPS (Frame Per Second)
	unsigned int	m_nFPSFrameCount;	// FPS ī����
	float			m_fElapsedTime;		// ��� �ð�
	float			m_fWorldTime;		// ���α׷� ���� �� �� ��� �ð�

public:
	Timer();
	~Timer();

	void InitTimer();					// Ÿ�̸� �ʱ�ȭ
	void Update(float lockFPS = 0.0f);	// ������Ʈ (FPS ���� ��, 0 = ���� ����)

	unsigned int GetFPS() const { return m_nFrameRate; }
	float GetDeltaTime() const { return m_fDeltaTime; }
	float GetWorldTime() const { return m_fWorldTime; }

	float GetTimeScale() { return m_fTimeScale; }
	void SetTimeScale(float s) { m_fTimeScale = s; }
};

