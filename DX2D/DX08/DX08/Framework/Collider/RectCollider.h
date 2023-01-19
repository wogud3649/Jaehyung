#pragma once
class RectCollider
{
public:
	RectCollider(Vector2 size);
	~RectCollider();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransform() { return _transform; }

	void SetRed() { _colorBuffer->_data.color = { 1,0,0,1 }; }
	void SetGreen() { _colorBuffer->_data.color = { 0,1,0,1 }; }

private:
	void CreateData();
	void CreateVertices();

	Vector2 _size = { 0,0 };

	vector<Vertex_Basic> _vertices;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<ColorBuffer> _colorBuffer;

	shared_ptr<Transform> _transform;
};

