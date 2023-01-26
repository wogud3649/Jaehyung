#pragma once
class RectCollider;
class CircleCollider;

class Collider
{
public:
	enum Type
	{
		NONE,
		CIRCLE,
		RECT
	};

	Collider();
	~Collider();

	virtual void Update();
	virtual void Render();

	shared_ptr<Transform> GetTransform() { return _transform; }

	virtual void CreateData() abstract;

	bool IsCollision(shared_ptr<Collider> other, bool isObb = false);

	virtual bool IsCollision(Vector2 pos) abstract;
	virtual bool IsCollision(shared_ptr<CircleCollider> other, bool isObb = false) abstract;
	virtual bool IsCollision(shared_ptr<RectCollider> other, bool isObb = false) abstract;

	void SetRed() { _colorBuffer->_data.color = { 1,0,0,1 }; }
	void SetGreen() { _colorBuffer->_data.color = { 0,1,0,1 }; }

protected:
	Type _type = NONE;

	vector<Vertex_Basic> _vertices;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<ColorBuffer> _colorBuffer;

	shared_ptr<Transform> _transform;
};

