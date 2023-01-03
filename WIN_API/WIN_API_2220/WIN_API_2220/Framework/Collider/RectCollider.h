#pragma once
class RectCollider : public Collider
{
public:
	RectCollider(Vector2 _center, Vector2 size);
	~RectCollider();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	Vector2& GetSize() { return size; }

	float Left() { return _center.x - size.x * 0.5f; }
	float Top() { return _center.y - size.y * 0.5f; }
	float Right() { return _center.x + size.x * 0.5f; }
	float Bottom() { return _center.y + size.y * 0.5f; }

	virtual bool IsCollision(const Vector2& pos) override;
	virtual bool IsCollision(const shared_ptr<RectCollider> rect) override;
	virtual bool IsCollision(const shared_ptr<CircleCollider> circle) override;

	bool IsVCollision() { return _vCollision; }
	bool IsHCollision() { return _hCollision; }

private:
	Vector2 size = { 0.0f, 0.0f };

	bool _vCollision = false;
	bool _hCollision = false;
};

