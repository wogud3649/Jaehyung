Texture2D map: register(t0);
SamplerState samp :register(s0);

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv: UV;

	float2 maxFrame : MAXFRAME;
	float2 curFrame : CURFRAME;
};

// SV : SystemValue
float4 PS(PixelInput input) : SV_TARGET
{
	float2 spriteUV;
	float2 max = input.maxFrame;
	float2 cur = input.curFrame;
	spriteUV.x = input.uv.x / max.x + cur.x / max.x;
	spriteUV.y = input.uv.y / max.y + cur.y / max.y;

	return map.Sample(samp, spriteUV);
}