#include "stdafx.h"
#include "Shader.h"


Shader::Shader(wstring file, string vs, string ps)
{
	HRESULT hr;

	wstring path = L"../../_Shader/" + file + L".hlsl";

	hr = D3DX11CompileFromFile(path.c_str(), 0, 0, vs.c_str(), "vs_5_0", 0, 0, 0, &VsBlob, 0, 0);
	assert(SUCCEEDED(hr));

	hr = D3DX11CompileFromFile(path.c_str(), 0, 0, ps.c_str(), "ps_5_0", 0, 0, 0, &PsBlob, 0, 0);
	assert(SUCCEEDED(hr));

	hr = Device->CreateVertexShader(VsBlob->GetBufferPointer(), VsBlob->GetBufferSize(), NULL, &VertexShader);
	assert(SUCCEEDED(hr));

	hr = Device->CreatePixelShader(PsBlob->GetBufferPointer(), PsBlob->GetBufferSize(), NULL, &PixelShader);
	assert(SUCCEEDED(hr));
}


Shader::~Shader()
{
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(PsBlob);
	SAFE_RELEASE(VsBlob);
	SAFE_RELEASE(PixelShader);
	SAFE_RELEASE(VertexShader);
}

void Shader::CreateinputLayout(D3D11_INPUT_ELEMENT_DESC * desc, UINT count)
{
	// 사용할 레이아웃 셋팅
	{
		HRESULT hr = Device->CreateInputLayout(desc, count,
			VsBlob->GetBufferPointer(), VsBlob->GetBufferSize(), &m_pVertexLayout);
		assert(SUCCEEDED(hr));
	}
}

void Shader::SetShader()
{
	DeviceContext->VSSetShader(VertexShader, 0, 0);
	DeviceContext->PSSetShader(PixelShader, 0, 0);

	DeviceContext->IASetInputLayout(m_pVertexLayout);
}
