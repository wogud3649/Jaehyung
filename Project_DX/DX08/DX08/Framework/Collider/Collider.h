#pragma once
class RectCollider;
class CircleCollider;

class Collider
{
protected:
	enum Type
	{
		NONE,
		CIRCLE,
		RECT
	};

public:
	Collider();
	~Collider();

	virtual void Update();
	virtual void Render();

	shared_ptr<Transform> GetTransform() { return _transform; }

	virtual void CreateData() abstract;

	HIT_RESULT IsCollision(shared_ptr<Collider> other, bool isObb = false);

	virtual HIT_RESULT IsCollision(Vector2 pos) abstract;
	virtual HIT_RESULT IsCollision(shared_ptr<CircleCollider> other, bool isObb = false) abstract;
	virtual HIT_RESULT IsCollision(shared_ptr<RectCollider> other, bool isObb = false) abstract;

	void SetRed() { _colorBuffer->_data.color = { 1,0,0,1 }; }
	void SetGreen() { _colorBuffer->_data.color = { 0,1,0,1 }; }

	void Activate() { _isActive = true; }
	void DeActivate() { _isActive = false; }

	bool GetActive() { return _isActive; }

	static bool _isDebug;

protected:
	Type _type = NONE;

	bool _isActive = true;

	vector<Vertex_Basic> _vertices;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<ColorBuffer> _colorBuffer;

	shared_ptr<Transform> _transform;
};