#include "stdafx.h"
#include "Sprite.h"


void Sprite::InitSprite(wstring key, float u1, float v1, float u2, float v2, int numX, int numY)
{
	Primitive2DObejct::Init();
	this->Init();

	// �ؽ��� �̹��� ����
	{
		m_pTexture = g_pTextureManager->GetTexture(key);
	}

	// ���� ��Ʈ���� ���� �� ���� ����
	{
		D3D11_BUFFER_DESC desc = { 0, };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(D3DXMATRIX);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		// ���ۿ� ���� ������
		D3D11_SUBRESOURCE_DATA data = { 0, };
		data.pSysMem = &m_matWorld;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &m_pWorldBuffer);
		assert(SUCCEEDED(hr));
	}

	m_fWidth = m_pTexture->stInfo.Width / numX;
	m_fHeight = m_pTexture->stInfo.Height / numY;

	// ���ؽ� �� ���� �� ���� ����
	{
		m_vecVertex.push_back(PTVertex(D3DXVECTOR3(-(m_fWidth * 0.5f),-(m_fHeight * 0.5f), 0), D3DXVECTOR2(u1, v2)));	// 0 : 0, 1
		m_vecVertex.push_back(PTVertex(D3DXVECTOR3(-(m_fWidth * 0.5f), (m_fHeight * 0.5f), 0), D3DXVECTOR2(u1, v1)));	// 1 : 0, 0
		m_vecVertex.push_back(PTVertex(D3DXVECTOR3( (m_fWidth * 0.5f), (m_fHeight * 0.5f), 0), D3DXVECTOR2(u2, v1)));	// 2 : 1, 0
		m_vecVertex.push_back(PTVertex(D3DXVECTOR3( (m_fWidth * 0.5f),-(m_fHeight * 0.5f), 0), D3DXVECTOR2(u2, v2)));	// 3 : 1, 1

		// ���� ������
		D3D11_BUFFER_DESC desc = { 0, };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(PTVertex) * m_vecVertex.size();
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		// ���ۿ� ���� ������
		D3D11_SUBRESOURCE_DATA data = { 0, };
		data.pSysMem = &m_vecVertex[0];

		// ���� ����(IN ���� ������, IN ������, OUT ������� ���ۿ� ���� ������)
		HRESULT hr = Device->CreateBuffer(&desc, &data, &m_pVertexBuffer);
		assert(SUCCEEDED(hr));
	}

	// �ε��� �� ���� �� ���� ����
	{
		m_vecIndex.push_back(0);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(2);

		m_vecIndex.push_back(0);
		m_vecIndex.push_back(2);
		m_vecIndex.push_back(3);

		// ���� ������
		D3D11_BUFFER_DESC desc = { 0, };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(UINT) * m_vecIndex.size();
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		// ���ۿ� ���� ������
		D3D11_SUBRESOURCE_DATA data = { 0, };
		data.pSysMem = &m_vecIndex[0];

		// ���� ����(IN ���� ������, IN ������, OUT ������� ���ۿ� ���� ������)
		HRESULT hr = Device->CreateBuffer(&desc, &data, &m_pIndexBuffer);
		assert(SUCCEEDED(hr));
	}

	// ���� �� ���� �� ���� ����
	{
		m_stColor = D3DXCOLOR(1, 1, 1, 1);

		// ���� ������
		D3D11_BUFFER_DESC desc = { 0, };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(D3DXCOLOR);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		// ���ۿ� ���� ������
		D3D11_SUBRESOURCE_DATA data = { 0, };
		data.pSysMem = &m_stColor;

		// ���� ����(IN ���� ������, IN ������, OUT ������� ���ۿ� ���� ������)
		HRESULT hr = Device->CreateBuffer(&desc, &data, &m_pColorBuffer);
		assert(SUCCEEDED(hr));
	}

	// ���̴� Ŭ���� ����
	{
		m_pShader = new Shader(L"Sprite");
		m_pShader->CreateinputLayout(PTElementDesc, PTElementCount);
	}

	// �������� ���� ����
	{
		this->CreateBorderVertexBuffer(0);
	}
}

Sprite::Sprite(wstring key, float u1, float v1, float u2, float v2)
{
	InitSprite(key, u1, v1, u2, v2);
}

Sprite::Sprite(wstring key, int numX, int numY, int index)
{
	float u1 = (index % numX) / (float)numX;
	float v1 = (index / numX) / (float)numY;
	float u2 = u1 + 1.0f / numX;
	float v2 = v1 + 1.0f / numY;

	InitSprite(key, u1, v1, u2, v2, numX, numY);
}

Sprite::~Sprite()
{
	Primitive2DObejct::~Primitive2DObejct();
}

void Sprite::Init()
{
	m_vPosition.x = WINSIZEX * 0.5f;
	m_vPosition.y = WINSIZEY * 0.5f;

	m_vSize.x = 1;
	m_vSize.y = 1;
}

void Sprite::Update()
{
	Primitive2DObejct::Update();
}

void Sprite::Render()
{
	if (m_pTexture)
		DeviceContext->PSSetShaderResources(0, 1, &m_pTexture->pSRV);

	Primitive2DObejct::Render();
}

void Sprite::SetConstantScale(float x, float y)
{
	m_vSize.x = x / m_fWidth;
	m_vSize.y = y / m_fHeight;
}

void Sprite::SetConstantScale(D3DXVECTOR2 s)
{
	this->SetConstantScale(s.x, s.y);
}

void Sprite::SetLBPosition(float x, float y)
{
	this->SetPosition(x + GetWidth() * 0.5f, y + GetHeight() * 0.5f);
}

void Sprite::SetLBPosition(D3DXVECTOR2 v)
{
	this->SetLBPosition(v.x, v.y);
}
