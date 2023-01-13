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

