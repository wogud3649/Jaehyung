Texture2D map: register(t0);
SamplerState samp :register(s0);

cbuffer SliderInfo : register(b1)
{
	float ratio;
	float opaque;
	int padding[2];
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
	if (input.uv.x > ratio)
	{
		result.x -= 0.7f;
		result.y -= 0.7f;
		result.z -= 0.7f;
		result.w = opaque;
	}
	return result;
}