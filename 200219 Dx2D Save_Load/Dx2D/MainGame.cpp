#include "stdafx.h"
#include "MainGame.h"


MainGame::MainGame()
{
	srand(time(NULL));

	SetViewProjectionMatrixes();
	SetBlendStates();

	CreateGameClasses();

	this->Init();
}

void MainGame::SetViewProjectionMatrixes()
{
	ViewProjectionDesc VPDesc;

	// 뷰 매트릭스 셋팅
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 lookAt(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&VPDesc.View, &eye, &lookAt, &up);
	D3DXMatrixTranspose(&VPDesc.View, &VPDesc.View);
	// 셰이더에서 매트릭스의 행과 열의 방향이 바껴있기 때문에 트랜스포즈를 해주어야 한다.

	// 프로젝션 매트릭스 셋팅
	D3DXMatrixOrthoOffCenterLH(&VPDesc.Projection, 0, (float)WINSIZEX, 0, (float)WINSIZEY, -1, 1);
	D3DXMatrixTranspose(&VPDesc.Projection, &VPDesc.Projection);

	// 버퍼 생성
	D3D11_BUFFER_DESC desc = { 0, };
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(ViewProjectionDesc);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// 버퍼에 담을 데이터
	D3D11_SUBRESOURCE_DATA data = { 0, };
	data.pSysMem = &VPDesc;

	HRESULT hr = Device->CreateBuffer(&desc, &data, &m_pViewProjBuffer);
}

void MainGame::SetBlendStates()
{
	D3D11_BLEND_DESC desc = { 0, };

	desc.RenderTarget[0].BlendEnable = false;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	Device->CreateBlendState(&desc, &m_pNormalBlendState);

	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	Device->CreateBlendState(&desc, &m_pAlphaBlendState);
}

MainGame::~MainGame()
{
	DeleteGameClasses();

	SAFE_RELEASE(m_pNormalBlendState);
	SAFE_RELEASE(m_pAlphaBlendState);

	SAFE_RELEASE(m_pViewProjBuffer);
}

void MainGame::CreateGameClasses()
{
	// 클래스 생성
	m_pPlayer = new Player;
	m_pMap = new Map;
	m_pMapObject = new MapObject;

	// 클래스 참조
	m_pPlayer->SetMap(m_pMap);
	m_pPlayer->SetMapObject(m_pMapObject);
	m_pMap->SetPlayer(m_pPlayer);
	m_pMapObject->SetMap(m_pMap);
	m_pMapObject->SetPlayer(m_pPlayer);

	m_pRect = new Rect;
}

void MainGame::DeleteGameClasses()
{
	SAFE_DELETE(m_pMapObject);
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pPlayer);
}

void MainGame::Init()
{
	SAFE_INIT(m_pMap);
	SAFE_INIT(m_pMapObject);
	SAFE_INIT(m_pPlayer);

	SAFE_INIT(m_pRect);
}

void MainGame::Update()
{
	if (g_pKeyManager->isOnceKeyDown(VK_F9)) // 게임 초기화
		this->Init();

	SAFE_UPDATE(m_pPlayer);
	SAFE_UPDATE(m_pMap);
	SAFE_UPDATE(m_pMapObject);

	static float rtPos[2];
	static float rot[3];

	ImGui::DragFloat2("RectPos", rtPos, 1.0f, 50, 670);
	ImGui::DragFloat3("Rot", rot);

	m_pRect->SetPosition(rtPos[0], rtPos[1]);
	m_pRect->SetRotation(rot[0], rot[1], rot[2]);
	SAFE_UPDATE(m_pRect);

	if (OBB2D(m_pPlayer->GetWMatrix(), m_pRect->GetWMatrix()))
		m_pRect->SetColor(D3DXCOLOR(1, 0, 0, 1));
	else
		m_pRect->SetColor(D3DXCOLOR(0, 1, 0, 1));
}

void MainGame::Render()
{
	D3DXCOLOR Map = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)Map);
	DeviceContext->VSSetConstantBuffers(0, 1, &m_pViewProjBuffer);

	DeviceContext->OMSetBlendState(m_pAlphaBlendState, NULL, 0xFF);

	SAFE_RENDER(m_pMap);
	SAFE_RENDER(m_pMapObject);
	SAFE_RENDER(m_pPlayer);

	SAFE_RENDER(m_pRect);

	g_pTextManager->AlphabetRender("ABCDEFG", 10, WINSIZEY - 60, 50);

	DeviceContext->OMSetBlendState(m_pNormalBlendState, NULL, 0xFF);

	ImGui::Render();

	SwapChain->Present(0, 0);
}