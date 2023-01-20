#pragma once
class RectCollider
{
public:
	struct OBB_DESC
	{
		Vector2 position;
		Vector2 direction[2]; // 가로 세로 벡터
		float length[2]; // 가로 세로 길이
	};

	RectCollider(Vector2 size);
	~RectCollider();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransform() { return _transform; }

	bool IsCollision(shared_ptr<CircleCollider> other);

	void SetRed() { _colorBuffer->_data.color = { 1,0,0,1 }; }
	void SetGreen() { _colorBuffer->_data.color = { 0,1,0,1 }; }

	OBB_DESC GetOBB();

	float SeparateAxis(Vector2 separate, Vector2 e1, Vector2 e2);

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

