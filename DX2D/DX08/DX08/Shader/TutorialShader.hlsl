Texture2D map: register(t0);
SamplerState samp :register(s0);

cbuffer World : register(b0)
{
	matrix world;
}

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
	float4 pos : POSITION;
	float2 uv : UV;
};

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv: UV;
};

PixelInput VS(VertexInput input)
{
	PixelInput result;
	result.pos = mul(input.pos, world);
	result.pos = mul(result.pos, view);
	result.pos = mul(result.pos, proj);
	result.uv = input.uv;

	return result;
}

// SV : SystemValue
float4 PS(PixelInput input) : SV_TARGET
{
	return map.Sample(samp,input.uv);
}