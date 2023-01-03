#pragma once
class Collider
{
public:
	enum class Type
	{
		NONE,
		CIRCLE,
		RECT
	};

	Collider();
	virtual ~Collider();

	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

	Vector2& GetCenter() { return _center; }

	void SetCenter(Vector2 center) { _center = center; }
	void SetRed() { _curPen = _pens[0]; }
	void SetGreen() { _curPen = _pens[1]; }

	bool IsCollision(shared_ptr<Collider> col);
	virtual bool IsCollision(const Vector2& pos) abstract;
	virtual bool IsCollision(const shared_ptr<class CircleCollider> circle) abstract;
	virtual bool IsCollision(const shared_ptr<class RectCollider> rect) abstract;

	bool _isActive = true;
protected:
	Type _type;
	vector<HPEN> _pens;
	HPEN _curPen;

	Vector2 _center;
};

