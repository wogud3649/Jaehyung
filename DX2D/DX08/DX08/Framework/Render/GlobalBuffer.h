#pragma once
class MatrixBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMMATRIX matrix = XMMatrixIdentity();
	};

	// ������� ��Ģ
	// 16����Ʈ�� ����� �÷����Ѵ�.
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

	// ������� ��Ģ
	// 16����Ʈ�� ����� �÷����Ѵ�.
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

	// ������� ��Ģ
	// 16����Ʈ�� ����� �÷����Ѵ�.
	ColorBuffer()
		: ConstantBuffer(&_data, sizeof(_data))
	{
	}

	virtual ~ColorBuffer() {}

	Data _data;
};

