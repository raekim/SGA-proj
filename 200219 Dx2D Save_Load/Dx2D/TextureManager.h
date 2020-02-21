#pragma once
#include "SingletonBase.h"

#define g_pTextureManager TextureManager::GetInstance()

struct Texture
{
	D3DX11_IMAGE_INFO			stInfo;
	ID3D11ShaderResourceView*	pSRV;
};

class TextureManager : public SingletonBase<TextureManager>
{
private:
	map<wstring, Texture>	m_mapTexture;

public:
	TextureManager();
	~TextureManager();

	void AddTexture(wstring key, wstring file, wstring path = L"../../_Images/");
	const Texture* GetTexture(wstring key);
};

