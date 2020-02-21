#pragma once
#include "SingletonBase.h"

#define g_pFileManager FileManager::GetInstance()

class FileManager :	public SingletonBase<FileManager>
{
//== ini 저장 ===================================================
	struct tagIniData
	{
		wstring section;
		wstring key;
		string value;
	};

private:
	typedef vector<tagIniData> vecIniData;
	typedef vector<tagIniData>::iterator vecIniDataIter;

private:
	vecIniData	m_vecIniData;

public:
	void AddSaveString(wstring section, wstring key, string value);
	void AddSaveInt(wstring section, wstring key, int value);
	void AddSavefloat(wstring section, wstring key, float value);
	void IniSave(wstring saveFileName);

	wstring LoadStringData(wstring saveFileName, wstring section, wstring key);
	int LoadIntegerData(wstring saveFileName, wstring section, wstring key);
	float LoadfloatData(wstring saveFileName, wstring section, wstring key);

//==============================================================

//== txt 저장 ===================================================
private:
	char* VectorArrayCombine(vector<string>& vecArray);
	vector<string> CharArraySeparation(char charArray[]);

public:
	void TxtSave(wstring saveFileName, vector<string>& vecData);
	vector<string> TxtLoad(wstring loadFileName);

//==============================================================
};

