#include "stdafx.h"
#include "TextManager.h"


TextManager::TextManager()
{
}


TextManager::~TextManager()
{
}

void TextManager::Init()
{
	g_pTextureManager->AddTexture(L"GoldNumber", L"GoldNumber.png", L"../../_Images/UIImages/");
	g_pTextureManager->AddTexture(L"BlueNumber", L"BlueNumber.png", L"../../_Images/UIImages/");
	g_pTextureManager->AddTexture(L"UpperLetter", L"UpperLetter.png", L"../../_Images/UIImages/");
	g_pTextureManager->AddTexture(L"LowerLetter", L"UpperLetter.png", L"../../_Images/UIImages/");

	for (int i = 0; i < 10; i++)
	{
		m_pGoldNumber[i] = new Sprite(L"GoldNumber", 10, 1, i);
		m_pBlueNumber[i] = new Sprite(L"BlueNumber", 10, 1, i);
	}

	for (int i = 0; i < 26; i++)
	{
		m_pUpperLetter[i] = new Sprite(L"UpperLetter", 26, 1, i);
		m_pLowerLetter[i] = new Sprite(L"UpperLetter", 26, 1, i);
	}
}

void TextManager::Release()
{
	for (int i = 0; i < 10; i++)
	{
		SAFE_DELETE(m_pGoldNumber[i]);
		SAFE_DELETE(m_pBlueNumber[i]);
	}

	for (int i = 0; i < 26; i++)
	{
		SAFE_DELETE(m_pUpperLetter[i]);
		SAFE_DELETE(m_pLowerLetter[i]);
	}
}

void TextManager::IntRender(int num, int x, int y, int size, NumberType type)
{
	vector<int> vecNumber;
	vecNumber.push_back(num % 10);

	while (num > 9)
	{
		num /= 10;
		vecNumber.push_back(num % 10);
	}

	int j = 0;
	for (int i = vecNumber.size() - 1; i >= 0; i--)
	{
		switch (type)
		{
		case NumberType::Gold:
			m_pGoldNumber[vecNumber[i]]->SetConstantScale(size, size);
			m_pGoldNumber[vecNumber[i]]->SetLBPosition(x + size * j * 0.7f, y);
			m_pGoldNumber[vecNumber[i]]->Update();
			m_pGoldNumber[vecNumber[i]]->Render();
			break;
		case NumberType::Blue:
			m_pBlueNumber[vecNumber[i]]->SetConstantScale(size, size);
			m_pBlueNumber[vecNumber[i]]->SetLBPosition(x + size * j * 0.7f, y);
			m_pBlueNumber[vecNumber[i]]->Update();
			m_pBlueNumber[vecNumber[i]]->Render();
			break;
		}

		j++;
	}
}

void TextManager::AlphabetRender(const char * str, int x, int y, int size)
{
	int posX = 0;

	for (int i = 0; i < strlen(str); i++)
	{
		int index = str[i] - 65;

		if (index <= 25)
		{
			m_pUpperLetter[index]->SetConstantScale(size, size);
			m_pUpperLetter[index]->SetLBPosition(x + posX, y);
			m_pUpperLetter[index]->Update();
			m_pUpperLetter[index]->Render();

			posX += size * 0.9f;
		}
		else
		{
			index -= 32;

			m_pLowerLetter[index]->SetConstantScale(size * 0.7f, size * 0.7f);
			m_pLowerLetter[index]->SetLBPosition(x + posX, y);
			m_pLowerLetter[index]->Update();
			m_pLowerLetter[index]->Render();

			posX += size * 0.6f;
		}
	}
}
