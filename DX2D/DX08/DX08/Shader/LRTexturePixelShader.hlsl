Texture2D map: register(t0);
SamplerState samp :register(s0);

cbuffer ReverseBuffer : register(b0)
{
	int reverse;
	int padding[3];
}

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv: UV;
};

// SV : SystemValue
float4 PS(PixelInput input) : SV_TARGET
{
	input.uv.x = abs(input.uv.x - reverse);

	return map.Sample(samp,input.uv);
}