#include "stdafx.h"
#include "KeyManager.h"


void KeyManager::Init()
{
	// 모든 값들을 false로 초기화
	m_bitKeyUp.reset();
	m_bitKeyDown.reset();
	m_bitKeyToggle.reset();
}

bool KeyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!m_bitKeyDown[key]) // 이전에 눌리지 않은 상태
		{
			m_bitKeyDown.set(key, true);
			return true;		// 키가 지금 막 눌렸다.
		}
	}
	else
	{
		m_bitKeyDown.set(key, false);
	}

	return false;
}

bool KeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		m_bitKeyUp.set(key, true);
	}
	else
	{
		if (m_bitKeyUp[key]) // 이전에 키가 눌려져 있는 상태 였다.
		{
			m_bitKeyUp.set(key, false);
			return true;
		}
	}

	return false;
}

bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;

	return false;
}

bool KeyManager::isToggleKey(int key)
{
	if (GetAsyncKeyState(key) & 0x0001)
	{
		m_bitKeyToggle[key].flip();
	}

	return m_bitKeyToggle[key];
}