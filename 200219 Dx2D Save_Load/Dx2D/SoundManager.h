#pragma once
#include "SingletonBase.h"


#include "FMOD/inc/fmod.hpp"
#pragma comment(lib, "FMOD/lib/fmodex_vc.lib")
using namespace FMOD;

#define SOUNDBUFFER (5)				// 사운드 갯수 설정
#define EXTRACHANNELBUFFER (5)		// 여유 채널 버퍼
#define TOTALSOUNDBUFFER (SOUNDBUFFER + EXTRACHANNELBUFFER)

#define g_pSoundManager SoundManager::GetInstance()

class SoundManager : public SingletonBase<SoundManager>
{
private:
	typedef map<string, Sound*>				mapSound;
	typedef map<string, Sound*>::iterator	mapSoundIter;
	typedef map<string, int>				mapChannerIndex;

private:
	mapSound			m_mapSound;	// 사운드 목록
	mapChannerIndex		m_mapIndex;	// 할당 된 채널 인덱스

	System*			m_pSystem;		// 사운드 시스템 클래스
	Channel**		m_ppChannel;	// 채널 클래스 포인터

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

