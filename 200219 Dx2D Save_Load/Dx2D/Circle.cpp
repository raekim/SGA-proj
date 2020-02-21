#include "stdafx.h"
#include "Circle.h"


Circle::Circle()
{
	Init();

	// 월드 매트릭스 셋팅 및 버퍼 생성
	{
		D3D11_BUFFER_DESC desc = { 0, };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(D3DXMATRIX);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		// 버퍼에 담을 데이터
		D3D11_SUBRESOURCE_DATA data = { 0, };
		data.pSysMem = &m_matWorld;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &m_pWorldBuffer);
		assert(SUCCEEDED(hr));
	}

	// 버텍스 값 셋팅 및 버퍼 생성
	{
		// 중점
		m_vecVertex.push_back(PCVertex(D3DXVECTOR3( 0, 0, 0), D3DXCOLOR(1, 1, 1, 1)));

		float angle = 0; // 라디안 값
		for (int i = 0; i < NUM_SLICE; i++)
		{
			float x = cosf(angle) * 0.5f;
			float y = sinf(angle) * 0.5f;

			m_vecVertex.push_back(PCVertex(D3DXVECTOR3(x, y, 0), D3DXCOLOR(1, 1, 1, 1)));

			angle += D3DX_PI * 2 / NUM_SLICE;
		}

		// 버퍼 설정값
		D3D11_BUFFER_DESC desc = { 0, };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(PCVertex) * m_vecVertex.size();
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		// 버퍼에 담을 데이터
		D3D11_SUBRESOURCE_DATA data = { 0, };
		data.pSysMem = &m_vecVertex[0];

		// 버퍼 생성(IN 버퍼 설정값, IN 데이터, OUT 만들어진 버퍼에 대한 포인터)
		HRESULT hr = Device->CreateBuffer(&desc, &data, &m_pVertexBuffer);
		assert(SUCCEEDED(hr));
	}

	// 인덱스 값 셋팅 및 버퍼 생성
	{
		for (int i = 0; i < NUM_SLICE; i++)
		{													// 0 1 2
			m_vecIndex.push_back(0);						// 0 0 0
			m_vecIndex.push_back((i + 1) % NUM_SLICE + 1);	// (1 2 3) % 3 => 1 2 0 + 1 => 2 3 1
			m_vecIndex.push_back(i + 1);					// 1 2 3
		}

		// 버퍼 설정값
		D3D11_BUFFER_DESC desc = { 0, };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(UINT) * m_vecIndex.size();
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		// 버퍼에 담을 데이터
		D3D11_SUBRESOURCE_DATA data = { 0, };
		data.pSysMem = &m_vecIndex[0];

		// 버퍼 생성(IN 버퍼 설정값, IN 데이터, OUT 만들어진 버퍼에 대한 포인터)
		HRESULT hr = Device->CreateBuffer(&desc, &data, &m_pIndexBuffer);
		assert(SUCCEEDED(hr));
	}

	// 색상 값 설정 및 버퍼 생성
	{
		m_stColor = D3DXCOLOR(1, 0, 0, 1);

		// 버퍼 설정값
		D3D11_BUFFER_DESC desc = { 0, };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(D3DXCOLOR);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		// 버퍼에 담을 데이터
		D3D11_SUBRESOURCE_DATA data = { 0, };
		data.pSysMem = &m_stColor;

		// 버퍼 생성(IN 버퍼 설정값, IN 데이터, OUT 만들어진 버퍼에 대한 포인터)
		HRESULT hr = Device->CreateBuffer(&desc, &data, &m_pColorBuffer);
		assert(SUCCEEDED(hr));
	}

	// 셰이더 클래스 생성
	{
		m_pShader = new Shader(L"Color");
		m_pShader->CreateinputLayout(PCElementDesc, PCElementCount);
	}

	// 보더라인 버퍼 생성
	{
		this->CreateBorderVertexBuffer(1);
	}
}


Circle::~Circle()
{
	Primitive2DObejct::~Primitive2DObejct();
}

void Circle::Init()
{
	Primitive2DObejct::Init();

	m_fRadius = m_vSize.x * 0.5f;
	m_fSpeed = 0.0f;
	m_fAngle = rand() % 360;
}

void Circle::Update()
{
	if (m_fSpeed != 0)
	{
		m_vPosition.x += cosf(D3DXToRadian(m_fAngle)) * m_fSpeed * g_pTimeManager->GetDeltaTime();
		m_vPosition.y += sinf(D3DXToRadian(m_fAngle)) * m_fSpeed * g_pTimeManager->GetDeltaTime();

		if (m_vPosition.x < m_fRadius ||
			m_vPosition.x > WINSIZEX - m_fRadius)
		{
			m_fAngle = 180.0f - m_fAngle;

			if (m_fAngle < 0.0f)
				m_fAngle = m_fAngle + 360.0f;
		}

		if (m_vPosition.y < m_fRadius ||
			m_vPosition.y > WINSIZEY - m_fRadius)
		{
			m_fAngle = 360.0f - m_fAngle;
		}
	}

	DeviceContext->UpdateSubresource(m_pColorBuffer, 0, 0, &m_stColor, 0, 0);

	Primitive2DObejct::Update();
}

void Circle::Render()
{
	Primitive2DObejct::Render();
}
