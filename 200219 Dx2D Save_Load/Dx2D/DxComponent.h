#pragma once
// Dx11 전역 변수:
extern IDXGISwapChain*			SwapChain;		// 렌더 버퍼(모든 윈도우) 관리 변수 : 프레젠트
extern ID3D11Device*			Device;			// 하나의 장치(창)에 대한 버퍼, 텍스쳐 등 생성 관리를 위한 인터페이스 (CPU)
extern ID3D11DeviceContext*		DeviceContext;	// 생성 된 리소스를 관리하기 위한 인터페이스 (GPU -> 텍스쳐 렌더링)
extern ID3D11RenderTargetView*	RTV;			// 렌더타겟 지정 포인터

//=======================================================================================
// 전역 구조체
struct WorldDesc
{
	D3DXMATRIX World;
};

struct ViewProjectionDesc
{
	D3DXMATRIX View;
	D3DXMATRIX Projection;
};

//=======================================================================================
// 유연한 버텍스 (Flexible Vertex)
struct PCVertex
{
	D3DXVECTOR3	Position;
	D3DXCOLOR	Color;

	PCVertex() {}
	PCVertex(D3DXVECTOR3 p, D3DXCOLOR c) : Position(p), Color(c) {}
};

static D3D11_INPUT_ELEMENT_DESC PCElementDesc[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};
static UINT PCElementCount = ARRAYSIZE(PCElementDesc);
//=======================================================================================
struct PTVertex
{
	D3DXVECTOR3	Position;
	D3DXVECTOR2	UV;

	PTVertex() {}
	PTVertex(D3DXVECTOR3 p, D3DXVECTOR2 uv) : Position(p), UV(uv) {}
};

static D3D11_INPUT_ELEMENT_DESC PTElementDesc[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};
static UINT PTElementCount = ARRAYSIZE(PTElementDesc);
//=======================================================================================