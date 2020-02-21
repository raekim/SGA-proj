#pragma once
#include "SingletonBase.h"


#include "FMOD/inc/fmod.hpp"
#pragma comment(lib, "FMOD/lib/fmodex_vc.lib")
using namespace FMOD;

#define SOUNDBUFFER (5)				// ���� ���� ����
#define EXTRACHANNELBUFFER (5)		// ���� ä�� ����
#define TOTALSOUNDBUFFER (SOUNDBUFFER + EXTRACHANNELBUFFER)

#define g_pSoundManager SoundManager::GetInstance()

class SoundManager : public SingletonBase<SoundManager>
{
private:
	typedef map<string, Sound*>				mapSound;
	typedef map<string, Sound*>::iterator	mapSoundIter;
	typedef map<string, int>				mapChannerIndex;

private:
	mapSound			m_mapSound;	// ���� ���
	mapChannerIndex		m_mapIndex;	// �Ҵ� �� ä�� �ε���

	System*			m_pSystem;		// ���� �ý��� Ŭ����
	Channel**		m_ppChannel;	// ä�� Ŭ���� ������

public:
	SoundManager();
	~SoundManager();

	void Init();
	void AddSound(string key, string filePath, bool bgm = false, bool loop = false);
	void ReleaseSound(string key);

	void Update();

	void Play(string key, float volume = 1.0f); // (0.0f ~ 1.0f)
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);

	bool IsPlaySound(string key);
	bool IsPauseSound(string key);
	
	void VolumeUp(string key);
	void VolumeDown(string key);
};

