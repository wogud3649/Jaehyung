Texture2D map: register(t0);
SamplerState samp :register(s0);

cbuffer ActionBuffer : register(b0)
{
	float2 startPos;
	float2 size;
	float2 imageSize;
	int padding0[2];
}

cbuffer ReverseBuffer : register(b1)
{
	int reverse;
	int padding[3];
}

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
	input.uv.x = abs(input.uv.x - reverse);

	float2 spriteUV;
	spriteUV.x = input.uv.x * (size.x / imageSize.x) + (startPos.x / imageSize.x);
	spriteUV.y = input.uv.y * (size.y / imageSize.y) + (startPos.y / imageSize.y);

	float4 result = map.Sample(samp, spriteUV);

	result.x = result.x + color.x;
	result.y = result.y + color.y;
	result.z = result.z + color.z;
	result.w = color.w;

	return result;
}