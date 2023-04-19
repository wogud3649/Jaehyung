Texture2D map: register(t0);
SamplerState samp :register(s0);

cbuffer ActionBuffer : register(b0)
{
	float2 startPos;
	float2 size;
	float2 imageSize;
	int padding0[2];
}

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
	//float2 spriteUV;
	//spriteUV.x = input.uv.x * (size.x / imageSize.x) + (startPos.x / imageSize.x);
	//spriteUV.y = input.uv.y * (size.y / imageSize.y) + (startPos.y / imageSize.y);

	float4 result = map.Sample(samp,input.uv);

	if (result.x > ratio)
	{
		result.x -= 0.7f;
		result.y -= 0.7f;
		result.z -= 0.7f;
		result.w = opaque;
	}

	return result;
}