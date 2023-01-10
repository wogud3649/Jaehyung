Texture2D map : register(t0);
SamplerState samp : register(s0);

struct VertexInput
{
	float pos : POSITION;
	float uv : UV;
};

struct PixelInput
{
	float pos : SV_POSITION;
	float uv : UV;
};

PixelInput VS(VertexInput input)
{
	PixelInput result;
	result.pos = input.pos;
	result.uv = input.uv;

	return result;
}

// SV : SystemValue
float4 PS(PixelInput input) : SV_TARGET
{
	return map.Sample(samp, input.uv);
}