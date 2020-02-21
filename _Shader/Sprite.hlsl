//========================================================
struct VertexInput
{
	float4 Position	: POSITION0;
	float2 UV		: UV0;
};

struct PixelInput
{
	float4 Position	: SV_POSITION;
	float2 UV		: UV0;
};
//========================================================

// ���ؽ� ���̴� ���� =============================
cbuffer VS_ViewProj : register(b0)
{
	matrix View;
	matrix Projection;
}

cbuffer VS_World : register(b1)
{
	matrix World;
}
//========================================================

// ���ؽ� ���̴�
PixelInput VS(VertexInput input)
{
	PixelInput output;

	output.Position = mul(input.Position, World);
	output.Position = mul(output.Position, View);
	output.Position = mul(output.Position, Projection);

	output.UV = input.UV;

	return output;
}

// �ȼ� ���̴� ���� ===============================
cbuffer PS_Color : register(b0)
{
	float4 Color;
}

SamplerState	Sampler : register(s0);
Texture2D		Texture : register(t0);
//========================================================

// �ȼ� ���̴�
float4 PS(PixelInput input) : SV_TARGET
{
	float4 tColor = Texture.Sample(Sampler, input.UV);

	if (tColor.r >= 248.0f / 255.0f && tColor.g == 0.0f && tColor.b >= 248.0f / 255.0f) // ����Ÿ ����
		tColor.a = 0.0f;

	return tColor * Color;
}
