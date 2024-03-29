#pragma once
class Quad
{
public:
	Quad();
	Quad(Vector2 size);
	Quad(wstring file);
	Quad(wstring file, Vector2 maxFrame);
	~Quad();

	virtual void Update();
	virtual void Render();
	void SetRender();

	virtual void CreateMaterial(wstring file);
	virtual void CreateMesh();

	void SetVS(shared_ptr<VertexShader> shader) { _vs = shader; }
	void SetPS(shared_ptr<PixelShader> shader) { _ps = shader; }
	
	Vector2 GetSize() { return _size; }

	shared_ptr<Transform> GetTransform() { return _transform; }

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