#include "stdafx.h"
#include "TextureManager.h"


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
	for (auto p : m_mapTexture)
		SAFE_RELEASE(p.second.pSRV);
	m_mapTexture.clear();
}

void TextureManager::AddTexture(wstring key, wstring file, wstring path)
{
	if (m_mapTexture.find(key) != m_mapTexture.end()) return;

	wstring fullPath = path + file;

	Texture texture;

	// 파일 정보 읽기 (사이즈 값 사용)
	{
		HRESULT hr;

		D3DX11GetImageInfoFromFile(fullPath.c_str(), NULL, &texture.stInfo, &hr);
		assert(SUCCEEDED(hr));
	}

	// 이미지 로드
	{
		HRESULT hr;

		D3DX11CreateShaderResourceViewFromFile(Device, fullPath.c_str(), NULL, NULL, &texture.pSRV, &hr);
		assert(SUCCEEDED(hr));
	}

	m_mapTexture[key] = texture;
}

const Texture* TextureManager::GetTexture(wstring key)
{
	if (m_mapTexture.find(key) == m_mapTexture.end()) return NULL;

	return &m_mapTexture[key];
}
