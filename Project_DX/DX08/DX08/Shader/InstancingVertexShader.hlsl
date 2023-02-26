cbuffer View : register(b1)
{
	matrix view;
}

cbuffer Projection : register(b2)
{
	matrix proj;
}

struct VertexInput
{
	float4 pos : POSITION; // ½Ã¸àÆ½ ³×ÀÓ
	float2 uv : UV;

	matrix transform : INSTANCE_TRANSFORM;
	float2 maxFrame : INSTANCE_MAXFRAME;
	float2 curFrame : INSTANCE_CURFRAME;
};

struct VertexOutput
{
	float4 pos : SV_POSITION;
	float2 uv: UV;

	float2 maxFrame : MAXFRAME;
	float2 curFrame : CURFRAME;
};

VertexOutput VS(VertexInput input)
{
	VertexOutput result;
	result.maxFrame = input.maxFrame;
	result.curFrame = input.curFrame;
	result.pos = mul(input.pos, input.transform);
	result.pos = mul(result.pos, view);
	result.pos = mul(result.pos, proj);
	result.uv = input.uv;

	return result;
}