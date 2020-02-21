#pragma once
class Shader
{
private:
	// 컴파일 (compile) : 고급 언어(HLSL : High Level Shading Language, 인간이 이해할 수 있는 언어) -> 기계어 (컴퓨터 언어)
	ID3D11VertexShader*		VertexShader;		// 버텍스 셰이더
	ID3D11PixelShader*		PixelShader;		// 픽셀 셰이더
	ID3D10Blob*				VsBlob;				// 컴파일 된 버텍스 셰이더
	ID3D10Blob*				PsBlob;				// 컴파일 된 픽셀 셰이더
	ID3D11InputLayout*		m_pVertexLayout;	// 입력 레이아웃 설정값

public:
	Shader(wstring file, string vs = "VS", string ps = "PS");
	~Shader();

	void CreateinputLayout(D3D11_INPUT_ELEMENT_DESC* desc, UINT count);
	void SetShader();
};

