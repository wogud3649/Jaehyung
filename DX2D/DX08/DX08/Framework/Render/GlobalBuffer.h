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

class ActionBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		Vector2 startPos;
		Vector2 size;
		Vector2 imageSize;
		int padding[2];
	};

	// 상수버퍼 규칙
	// 16바이트의 배수로 올려야한다.
	ActionBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{
	}

	virtual ~ActionBuffer() {}

	Data _data;
};

class ReverseBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		int reverse = 0;
		int padding[3];
	};

	// 상수버퍼 규칙
	// 16바이트의 배수로 올려야한다.
	ReverseBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{
	}

	virtual ~ReverseBuffer() {}

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

class FilterBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		int selected = 0;
		int value1 = 0;
		int value2 = 0;
		int value3 = 0;
		Vector2 imageSize;
		XMFLOAT2 padding;
	};

	// 상수버퍼 규칙
	// 16바이트의 배수로 올려야한다.
	FilterBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{
	}

	virtual ~FilterBuffer() {}

	Data _data;
};