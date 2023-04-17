Texture2D map: register(t0);
SamplerState samp :register(s0);

cbuffer SliderInfo : register(b1)
{
	float ratio;
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
	if (input.uv.x > ratio)
		return float4(0.0f,0.0f,0.0f,0.0f);
	float4 result = map.Sample(samp,input.uv);

	return result;
}