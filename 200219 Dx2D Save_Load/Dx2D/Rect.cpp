#include "stdafx.h"
#include "Rect.h"


Rect::Rect()
{
	Primitive2DObejct::Init();
	Init();

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

	// ���ؽ� �� ���� �� ���� ����
	{
		m_vecVertex.push_back(PCVertex(D3DXVECTOR3(-0.5f,-0.5f, 0), D3DXCOLOR(1, 1, 1, 1))); // 0
		m_vecVertex.push_back(PCVertex(D3DXVECTOR3(-0.5f, 0.5f, 0), D3DXCOLOR(1, 1, 1, 1))); // 1
		m_vecVertex.push_back(PCVertex(D3DXVECTOR3( 0.5f, 0.5f, 0), D3DXCOLOR(1, 1, 1, 1))); // 2
		m_vecVertex.push_back(PCVertex(D3DXVECTOR3(0.5f, -0.5f, 0), D3DXCOLOR(1, 1, 1, 1))); // 3

		// ���� ������
		D3D11_BUFFER_DESC desc = { 0, };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(PCVertex) * m_vecVertex.size();
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
		m_stColor = D3DXCOLOR(0, 1, 0, 1);

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
		m_pShader = new Shader(L"Color");
		m_pShader->CreateinputLayout(PCElementDesc, PCElementCount);
	}

	// �������� ���� ����
	{
		this->CreateBorderVertexBuffer(0);
	}
}


Rect::~Rect()
{
	Primitive2DObejct::~Primitive2DObejct();
}

void Rect::Init()
{
	m_fSpeed = 0.0f;
	m_fAngle = rand() % 360;
}

void Rect::Update()
{
	if (m_fSpeed != 0)
	{
		m_vPosition.x += cosf(D3DXToRadian(m_fAngle)) * m_fSpeed * g_pTimeManager->GetDeltaTime();
		m_vPosition.y += sinf(D3DXToRadian(m_fAngle)) * m_fSpeed * g_pTimeManager->GetDeltaTime();

		if (m_vPosition.x < m_vSize.x * 0.5f ||
			m_vPosition.x > WINSIZEX - m_vSize.x * 0.5f)
		{
			m_fAngle = 180.0f - m_fAngle;

			if (m_fAngle < 0.0f)
				m_fAngle = m_fAngle + 360.0f;
		}

		if (m_vPosition.y < m_vSize.y * 0.5f ||
			m_vPosition.y > WINSIZEY - m_vSize.y * 0.5f)
		{
			m_fAngle = 360.0f - m_fAngle;
		}
	}

	Primitive2DObejct::Update();
}

void Rect::Render()
{
	Primitive2DObejct::Render();
}
