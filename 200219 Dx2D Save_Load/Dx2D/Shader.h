#pragma once
class Shader
{
private:
	// ������ (compile) : ��� ���(HLSL : High Level Shading Language, �ΰ��� ������ �� �ִ� ���) -> ���� (��ǻ�� ���)
	ID3D11VertexShader*		VertexShader;		// ���ؽ� ���̴�
	ID3D11PixelShader*		PixelShader;		// �ȼ� ���̴�
	ID3D10Blob*				VsBlob;				// ������ �� ���ؽ� ���̴�
	ID3D10Blob*				PsBlob;				// ������ �� �ȼ� ���̴�
	ID3D11InputLayout*		m_pVertexLayout;	// �Է� ���̾ƿ� ������

public:
	Shader(wstring file, string vs = "VS", string ps = "PS");
	~Shader();

	void CreateinputLayout(D3D11_INPUT_ELEMENT_DESC* desc, UINT count);
	void SetShader();
};

