Texture2D map: register(t0);
SamplerState samp :register(s0);

cbuffer SpriteBuffer : register(b0)
{
	float2 maxFrame; // (10, 8)
	float2 curFrame; // (1, 0)
}

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv: UV;
};

// SV : SystemValue
float4 PS(PixelInput input) : SV_TARGET
{
	float2 spriteUV;
	spriteUV.x = input.uv.x / maxFrame.x + curFrame.x / maxFrame.x;
	spriteUV.y = input.uv.y / maxFrame.y + curFrame.y / maxFrame.y;

	return map.Sample(samp, spriteUV);
}