Texture2D map: register(t0);
SamplerState samp :register(s0);

cbuffer ButtonInfo : register(b1)
{
	int state;
	float hover;
	float click;
	int padding;
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
	[branch]
	if (state == 0)
		return result;
	else if (state == 1)
	{
		result -= float4(hover, hover, hover, 0.0f);
		return result;
	}
	else if (state == 2)
	{
		result -= float4(click, click, click, 0.0f);
		return result;
	}

	return result;
}