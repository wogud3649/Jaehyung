#pragma once
class CircleCollider : public Collider, public enable_shared_from_this<CircleCollider>
{
public:
	CircleCollider(Vector2 _center, float radius);
	~CircleCollider();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	float& GetRadius() { return radius; }

	virtual bool IsCollision(const Vector2& pos) override;
	virtual bool IsCollision(const shared_ptr<CircleCollider> circle) override;
	virtual bool IsCollision(const shared_ptr<class RectCollider> rect) override;

private:
	float radius;
};

