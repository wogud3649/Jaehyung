#pragma once
class IndexBuffer
{
public:
	IndexBuffer(void* data, UINT count);
	~IndexBuffer();

	void IASetIndexBuffer();
	void CreateIndexBuffer(void* data);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
	UINT _count;
};

