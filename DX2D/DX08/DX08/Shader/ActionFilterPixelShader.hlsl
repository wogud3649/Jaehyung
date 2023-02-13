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

cbuffer FilterBuffer : register(b2)
{
	int selected;
	int value1;
	int value2;
	int value3;
	float2 padding2;
	float2 radialCenter;
}

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv: UV;
};

float4 Mosaic(float2 uv)
{
	float x = floor(uv.x * value1);
	float y = floor(uv.y * value1);

	float2 temp;
	temp.x = x / value1;
	temp.y = y / value1;

	return map.Sample(samp, temp);
}

float4 Blur(float2 uv)
{
	float4 result = 0;

	for (int i = 0; i < value2; i++)
	{
		float divX = (i + 1) / imageSize.x;
		float divY = (i + 1) / imageSize.y;

		result += map.Sample(samp, float2(uv.x + divX, uv.y));
		result += map.Sample(samp, float2(uv.x - divX, uv.y));
		result += map.Sample(samp, float2(uv.x, uv.y + divY));
		result += map.Sample(samp, float2(uv.x, uv.y - divY));
	}

	result /= 4 * value2;

	return result;
}

float4 OctaBlur(float2 uv)
{
	float4 result = 0;

	for (int i = 0; i < value2; i++)
	{
		float divX = (i + 1) / imageSize.x;
		float divY = (i + 1) / imageSize.y;

		result += map.Sample(samp, float2(uv.x + divX, uv.y));
		result += map.Sample(samp, float2(uv.x - divX, uv.y));
		result += map.Sample(samp, float2(uv.x, uv.y + divY));
		result += map.Sample(samp, float2(uv.x, uv.y - divY));

		result += map.Sample(samp, float2(uv.x + divX, uv.y + divY));
		result += map.Sample(samp, float2(uv.x - divX, uv.y + divY));
		result += map.Sample(samp, float2(uv.x + divX, uv.y - divY));
		result += map.Sample(samp, float2(uv.x - divX, uv.y - divY));
	}

	result /= 8 * value2;

	return result;
}

static const float weight[13] =
{
	0.0561f, 0.1353f, 0.2730f, 0.4868f, 0.7261f, 0.9231f,
	0.1f,
	0.9231f, 0.7261f, 0.4868f, 0.2730f, 0.1353f, 0.0561f
};

float4 GaussianBlur(float2 uv)
{
	float divX = 1.0f / imageSize.x;
	float divY = 1.0f / imageSize.y;

	float sum = 0;
	float4 result = 0;

	for (int i = -6; i <= 6; i++)
	{
		float2 temp = uv + float2(divX * i * value2, 0);
		result += weight[6 + i] * map.Sample(samp, temp);

		temp = uv + float2(0, divY * i * value2);
		result += weight[6 + i] * map.Sample(samp, temp);

		sum += weight[6 + i] * 2;
	}

	result /= sum;

	return result;
}

float4 RadialBlur(float2 uv)
{
	float2 offset = float2(0.5f, 0.5f);
	float2 radiusUV = uv - offset;
	float r = length(radiusUV);
	radiusUV /= r;

	r = saturate(2 * r / value1);

	float2 delta = radiusUV * r * r * value3 / value2;

	float4 result = 0;

	for (int i = 0; i < value2; i++)
	{
		result += map.Sample(samp, uv);
		uv += delta;
	}

	result /= value2;

	return result;
}

float4 OutLine(float2 uv)
{
	float4 result;

	result = map.Sample(samp, uv);

	if (result.w < 0.2f && result.w > 0.01f)
	{
		return float4 (1, 0, 0, 1);
	}

	return result;
}

// SV : SystemValue
float4 PS(PixelInput input) : SV_TARGET
{
	input.uv.x = abs(input.uv.x - reverse);

	float2 spriteUV;
	spriteUV.x = input.uv.x * (size.x / imageSize.x) + (startPos.x / imageSize.x);
	spriteUV.y = input.uv.y * (size.y / imageSize.y) + (startPos.y / imageSize.y);

	[branch]
	if (selected == 0)
		return map.Sample(samp, spriteUV);
	else if (selected == 1)
		return Mosaic(spriteUV);
	else if (selected == 2)
		return Blur(spriteUV);
	else if (selected == 3)
		return OctaBlur(spriteUV);
	else if (selected == 4)
		return GaussianBlur(spriteUV);
	else if (selected == 5)
		return RadialBlur(spriteUV);
	else if (selected == 6)
		return OutLine(spriteUV);

	return map.Sample(samp, spriteUV);
}