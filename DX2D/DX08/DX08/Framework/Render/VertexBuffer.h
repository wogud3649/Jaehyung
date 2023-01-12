#pragma once
class VertexBuffer
{
public:
	VertexBuffer(void* data, UINT stride, UINT count, UINT offset = 0);
	~VertexBuffer();

	void CreateVertexBuffer();

	void Set(int slot = 0);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;

	void* _data;
	UINT _count;
	UINT _stride;
	UINT _offset;
};

