cbuffer ColorBuffer : register(b0)
{
	float4 color;
}

struct PixelInput
{
	float4 pos : SV_POSITION;
};

// SV : SystemValue
float4 PS(PixelInput input) : SV_TARGET
{
	return color;
}