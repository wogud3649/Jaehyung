#pragma once
class MatrixBuffer;

class Transform
{
public:
	Transform();
	~Transform();

	void UpdateSRT();
	void Update();
	void SetBuffer(UINT slot);

	void SetScale(Vector2 scale)	{ _scale = scale; }
	void AddScale(Vector2 scale)	{ _scale += scale; }
	void AddScaleX(float xScale)	{ _scale.x += xScale; }
	void AddScaleY(float yScale)	{ _scale.y += yScale; }

	void SetAngle(float angle)		{ _angle = angle; }
	void AddAngle(float angle)		{ _angle += angle; }

	void SetPos(Vector2 pos)		{ _pos = pos; }
	void SetX(float x)				{ _pos.x = x; }
	void SetY(float y)				{ _pos.y = y; }
	void Move(Vector2 vector)		{ _pos += vector; }
	void MoveX(float distance)		{ _pos.x += distance; }
	void MoveY(float distance)		{ _pos.y += distance; }

	Vector2 GetScale()				{ return _scale; }
	float GetAngle()				{ return _angle; }
	Vector2 GetPos()				{ return _pos; }

	Vector2 GetWorldScale();
	float GetWorldAngle();
	Vector2 GetWorldPos();

	void SetParent(shared_ptr<Transform> parent)	{ _parent = parent; }

	const XMMATRIX& GetMatrix() { return _srtMatrix; }

private:
	shared_ptr<MatrixBuffer> _world;

	Vector2		_scale	=	{ 1.0f ,1.0f };
	float		_angle	=	0.0f;
	Vector2		_pos	=	{ 0.0f, 0.0f };

	XMMATRIX _scaleM	=	XMMatrixIdentity();
	XMMATRIX _rotationM	=	XMMatrixIdentity();
	XMMATRIX _tranlateM	=	XMMatrixIdentity();

	XMMATRIX _srtMatrix	=	XMMatrixIdentity();

	weak_ptr<Transform> _parent;
};

