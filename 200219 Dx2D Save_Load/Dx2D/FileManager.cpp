#include "stdafx.h"
#include "FileManager.h"


void FileManager::AddSaveString(wstring section, wstring key, string value)
{
	tagIniData iniData;
	iniData.section = section;
	iniData.key = key;
	iniData.value = value;

	m_vecIniData.push_back(iniData);
}

void FileManager::AddSaveInt(wstring section, wstring key, int value)
{
	tagIniData iniData;
	iniData.section = section;
	iniData.key = key;

	char szBuf[1024];
	_itoa_s(value, szBuf, 10);
	iniData.value = szBuf;

	//sprintf_s(szBuf, "%d", value);

	m_vecIniData.push_back(iniData);
}

void FileManager::AddSavefloat(wstring section, wstring key, float value)
{
	tagIniData iniData;
	iniData.section = section;
	iniData.key = key;

	char szBuf[1024];
	sprintf_s(szBuf, "%f", value);
	iniData.value = szBuf;

	m_vecIniData.push_back(iniData);
}

void FileManager::IniSave(wstring saveFileName)
{
	wstring fullPath = L"../../_Files/" + saveFileName + L".ini";

	wstring wstr;

	for (int i = 0; i < m_vecIniData.size(); i++)
	{
		wstr.assign(m_vecIniData[i].value.begin(), m_vecIniData[i].value.end());

		WritePrivateProfileString(m_vecIniData[i].section.c_str(),
			m_vecIniData[i].key.c_str(), wstr.c_str(), fullPath.c_str());
	}
	m_vecIniData.clear();
}

wstring FileManager::LoadStringData(wstring saveFileName, wstring section, wstring key)
{
	wstring fullPath = L"../../_Files/" + saveFileName + L".ini";

	LPWSTR data = new WCHAR[1024];
	GetPrivateProfileString(section.c_str(), key.c_str(), L"", data, 1024, fullPath.c_str());

	return data;
}

int FileManager::LoadIntegerData(wstring saveFileName, wstring section, wstring key)
{
	wstring fullPath = L"../../_Files/" + saveFileName + L".ini";

	return GetPrivateProfileInt(section.c_str(), key.c_str(), 0, fullPath.c_str());
}

float FileManager::LoadfloatData(wstring saveFileName, wstring section, wstring key)
{
	wstring fullPath = L"../../_Files/" + saveFileName + L".ini";

	LPWSTR data = new WCHAR[1024];
	GetPrivateProfileString(section.c_str(), key.c_str(), L"", data, 1024, fullPath.c_str());

	wstring wstr = data;
	string str;
	str.assign(wstr.begin(), wstr.end());
	
	char* above;
	char* below;

	above = strtok_s((char*)str.c_str(), ".", &below);

	int nAbove = atoi(above);
	int nBelow = atoi(below);

	int decimal = 1;
	int temp = nBelow;
	while (temp > 0)
	{
		decimal *= 10;
		temp /= 10;
	}

	return nAbove + nBelow / (float)decimal;
}

char * FileManager::VectorArrayCombine(vector<string>& vecArray)
{
	char szBuf[1024];
	ZeroMemory(szBuf, sizeof(szBuf));

	// strcpy : 문자열 복사
	// strcat : 문자열 붙이기
	// strcmp : 문자열 비교
	for (int i = 0; i < vecArray.size(); i++)
	{
		strcat_s(szBuf, vecArray[i].c_str());

		if (i < vecArray.size() - 1)
			strcat_s(szBuf, ",");
	}

	return szBuf;
}

vector<string> FileManager::CharArraySeparation(char charArray[])
{
	vector<string> vecArray;
	const char* separator = ",";
	char* token;
	char* remained;

	token = strtok_s(charArray, separator, &remained);
	if (token != NULL)
		vecArray.push_back(token);

	while ((token = strtok_s(remained, separator, &remained)) != NULL)
	{
		vecArray.push_back(token);
	}

	return vecArray;
}

void FileManager::TxtSave(wstring saveFileName, vector<string>& vecData)
{
	HANDLE file;
	char szBuf[1024];
	DWORD write;

	// '\0' : 널문자 - 문자열이 끝났음을 알려줌

	strncpy_s(szBuf, 1024, VectorArrayCombine(vecData), 1022);

	wstring fullPath = L"../../_Files/" + saveFileName + L".txt";

	file = CreateFile(fullPath.c_str(),
		GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, szBuf, strlen(szBuf), &write, NULL);

	CloseHandle(file);
}

vector<string> FileManager::TxtLoad(wstring loadFileName)
{
	HANDLE file;
	char szBuf[1024];
	DWORD read;

	ZeroMemory(szBuf, sizeof(szBuf));

	wstring fullPath = L"../../_Files/" + loadFileName + L".txt";

	file = CreateFile(fullPath.c_str(),
		GENERIC_READ, NULL, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, szBuf, 1024, &read, NULL);

	CloseHandle(file);

	return CharArraySeparation(szBuf);
}
