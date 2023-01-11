#pragma once
class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void CreateVertices();
	void CreateVertexBuffer();

	void Set(int slot = 0);

private:
	vector<Vertex> vertices;

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;

	UINT stride;
	UINT offset;
};

