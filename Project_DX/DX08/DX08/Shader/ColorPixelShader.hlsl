Texture2D map: register(t0);
SamplerState samp :register(s0);

cbuffer ColorBuffer : register(b2)
{
	float4 color;
}

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv: UV;
};

// SV : SystemValue
float4 PS(PixelInput input) : SV_TARGET
{
	float4 result = map.Sample(samp,input.uv);

	result.x = color.x;
	result.y = color.y;
	result.z = color.z;
	result.w = color.w;

	return result;
}