#pragma once
// Dx11 ���� ����:
extern IDXGISwapChain*			SwapChain;		// ���� ����(��� ������) ���� ���� : ������Ʈ
extern ID3D11Device*			Device;			// �ϳ��� ��ġ(â)�� ���� ����, �ؽ��� �� ���� ������ ���� �������̽� (CPU)
extern ID3D11DeviceContext*		DeviceContext;	// ���� �� ���ҽ��� �����ϱ� ���� �������̽� (GPU -> �ؽ��� ������)
extern ID3D11RenderTargetView*	RTV;			// ����Ÿ�� ���� ������

//=======================================================================================
// ���� ����ü
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
// ������ ���ؽ� (Flexible Vertex)
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