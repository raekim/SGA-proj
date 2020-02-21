//========================================================
struct VertexInput
{
	float4 Position	: POSITION0;
	float4 Color	: COLOR0;
};

struct PixelInput
{
	float4 Position	: SV_POSITION;
	float4 Color	: COLOR0;
};
//========================================================

// 버텍스 셰이더 용 콘스탄트 버퍼 =============================
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

// 버텍스 셰이더
PixelInput VS(VertexInput input)
{
	PixelInput output;

	output.Position = input.Position;
	output.Color = input.Color;

	return output;
}

// 픽셀 셰이더 용 콘스탄트 버퍼 ===============================
cbuffer PS_Color : register(b0)
{
	float4 Color;
}
//========================================================

// 픽셀 셰이더
float4 PS(PixelInput input) : SV_TARGET
{
    return input.Color;
}
