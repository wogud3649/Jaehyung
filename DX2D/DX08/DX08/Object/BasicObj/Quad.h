#pragma once
class Quad
{
public:
	Quad(wstring file);
	~Quad();

	void Update();
	void Render();

	void CreateMaterial(wstring file);
	void CreateMesh();

private:
	Vector2 _size;

	vector<UINT> _indices;
	vector<Vertex> _vertices;

	shared_ptr<VertexBuffer>	_vertexBuffer;
	shared_ptr<IndexBuffer>		_indexBuffer;

	shared_ptr<VertexShader>	_vs;
	shared_ptr<PixelShader>		_ps;
	shared_ptr<SRV>				_srv;
	shared_ptr<SamplerState>	_sampler;

	shared_ptr<MatrixBuffer> _world;
};

