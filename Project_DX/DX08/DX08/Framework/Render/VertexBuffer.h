#pragma once
class VertexBuffer
{
public:
	VertexBuffer(void* data, UINT stride, UINT count, UINT offset = 0, bool instance = false);
	~VertexBuffer();

	void CreateVertexBuffer();
	void CreateVertexBuffer_Instance();

	void IASet(int slot = 0);

	void Update();

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
	D3D11_MAPPED_SUBRESOURCE _subResource;

	void* _data;
	UINT _count;
	UINT _stride;
	UINT _offset;

	bool _instance = false;
};

