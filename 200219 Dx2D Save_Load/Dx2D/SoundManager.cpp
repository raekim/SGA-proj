#include "stdafx.h"
#include "SoundManager.h"


SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
	for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		m_ppChannel[i]->stop();

	delete[] m_ppChannel;

	mapSoundIter iter;
	for (iter = m_mapSound.begin(); iter != m_mapSound.end(); iter++)
	{
		iter->second->release();
	}
	m_mapSound.clear();

	m_pSystem->release();
	m_pSystem->close();
}

void SoundManager::Init()
{
	System_Create(&m_pSystem);

	m_pSystem->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	m_ppChannel = new Channel*[TOTALSOUNDBUFFER];
	memset(m_ppChannel, 0, sizeof(Channel*) * TOTALSOUNDBUFFER);
}

void SoundManager::AddSound(string key, string filePath, bool bgm, bool loop)
{
	string fullPath = "../../_Sounds/" + filePath;

	FMOD_RESULT result;

	if (loop)
	{
		if (bgm)
			result = m_pSystem->createStream(fullPath.c_str(), FMOD_LOOP_NORMAL, NULL, &m_mapSound[key]);
		else
			result = m_pSystem->createSound(fullPath.c_str(), FMOD_LOOP_NORMAL, NULL, &m_mapSound[key]);
	}
	else
	{
		if (bgm)
			result = m_pSystem->createStream(fullPath.c_str(), FMOD_DEFAULT, NULL, &m_mapSound[key]);
		else
			result = m_pSystem->createSound(fullPath.c_str(), FMOD_DEFAULT, NULL, &m_mapSound[key]);
	}

	assert(!result);

	m_mapIndex[key] = -1;
}

void SoundManager::ReleaseSound(string key)
{
	for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		m_ppChannel[i]->stop();

	m_mapSound[key]->release();
	m_mapSound.erase(key);
}

void SoundManager::Update()
{
	m_pSystem->update();
}

void SoundManager::Play(string key, float volume)
{
	bool isPlay = false;

	if (m_mapIndex[key] != -1)
	{
		m_ppChannel[m_mapIndex[key]]->isPlaying(&isPlay);

		if (!isPlay)
			m_mapIndex[key] = -1;
	}

	for (int i = 0; i < SOUNDBUFFER; i++)
	{
		m_ppChannel[i]->isPlaying(&isPlay);		// 빈채널 찾기

		if (!isPlay && m_mapIndex[key] == -1)
		{
			m_pSystem->playSound(FMOD_CHANNEL_FREE, m_mapSound[key], false, &m_ppChannel[i]);
			m_ppChannel[i]->setVolume(volume);

			m_mapIndex[key] = i; // 재생 중인 채널 저장
			break;
		}
	}
}

void SoundManager::Stop(string key)
{
	m_ppChannel[m_mapIndex[key]]->stop();
}

void SoundManager::Pause(string key)
{
	m_ppChannel[m_mapIndex[key]]->setPaused(true);
}

void SoundManager::Resume(string key)
{
	m_ppChannel[m_mapIndex[key]]->setPaused(false);
}

bool SoundManager::IsPlaySound(string key)
{
	bool isPlay = false;

	m_ppChannel[m_mapIndex[key]]->isPlaying(&isPlay);

	return isPlay;
}

bool SoundManager::IsPauseSound(string key)
{
	bool isPause = false;

	m_ppChannel[m_mapIndex[key]]->getPaused(&isPause);

	return isPause;
}

void SoundManager::VolumeUp(string key)
{
	float volume = 1.0f;

	m_ppChannel[m_mapIndex[key]]->getVolume(&volume);
	m_ppChannel[m_mapIndex[key]]->setVolume(volume + 0.01f);
}

void SoundManager::VolumeDown(string key)
{
	float volume = 1.0f;

	m_ppChannel[m_mapIndex[key]]->getVolume(&volume);
	m_ppChannel[m_mapIndex[key]]->setVolume(volume - 0.01f);
}
