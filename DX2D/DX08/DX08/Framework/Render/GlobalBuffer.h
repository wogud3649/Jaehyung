#pragma once
class MatrixBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMMATRIX matrix = XMMatrixIdentity();
	};

	// 상수버퍼 규칙
	// 16바이트의 배수로 올려야한다.
	MatrixBuffer()
	: ConstantBuffer(&_data, sizeof(_data))
	{
		
	}

	virtual ~MatrixBuffer() {}

	void SetData(XMMATRIX value)
	{
		_data.matrix = XMMatrixTranspose(value);
	}

private:
	Data _data;
};

class SpriteBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		Vector2 maxFrame = { 0.0f,0.0f };
		Vector2 curFrame = { 0.0f,0.0f };
	};

	// 상수버퍼 규칙
	// 16바이트의 배수로 올려야한다.
	SpriteBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{
	}

	virtual ~SpriteBuffer() {}

	Data _data;
};

class ColorBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMFLOAT4 color = { 0,1,0,1 };
	};

	// 상수버퍼 규칙
	// 16바이트의 배수로 올려야한다.
	ColorBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{
	}

	virtual ~ColorBuffer() {}

	Data _data;
};

