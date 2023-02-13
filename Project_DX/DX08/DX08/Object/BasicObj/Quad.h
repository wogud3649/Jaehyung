#pragma once
class Quad
{
public:
	Quad();
	Quad(wstring file);
	~Quad();

	virtual void Update();
	virtual void Render();

	virtual void CreateMaterial(wstring file);
	virtual void CreateMesh();

	void SetVS(shared_ptr<VertexShader> shader) { _vs = shader; }
	void SetPS(shared_ptr<PixelShader> shader) { _ps = shader; }

	shared_ptr<Transform> GetTransform() { return _transform; }
	Vector2& GetSize() { return _size; }

	Vector2 GetImageSize() { return _size; }

protected:
	Vector2 _size;

	// Mesh
	vector<UINT> _indices;
	vector<Vertex> _vertices;

	shared_ptr<VertexBuffer>	_vertexBuffer;
	shared_ptr<IndexBuffer>		_indexBuffer;

	// Material 
	shared_ptr<VertexShader>	_vs;
	shared_ptr<PixelShader>		_ps;
	shared_ptr<SRV>				_srv;

	shared_ptr<Transform> _transform;
};