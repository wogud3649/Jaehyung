#pragma once
class CircleCollider : public Collider, public enable_shared_from_this<CircleCollider>
{
public:
	friend RectCollider;

	CircleCollider(float radius);
	~CircleCollider();

	virtual void CreateData() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual HIT_RESULT IsCollision(Vector2 pos) override;
	virtual HIT_RESULT IsCollision(shared_ptr<CircleCollider> other, bool isObb = false) override;
	virtual HIT_RESULT IsCollision(shared_ptr<RectCollider> other, bool isObb = false) override;

	virtual HIT_RESULT Block(shared_ptr<CircleCollider> other);
	virtual HIT_RESULT Block(shared_ptr<RectCollider> other);

	float WorldRadius();

private:
	Vector2 GetCloserVertex(shared_ptr<RectCollider> rect);

	void CreateVertices();

	float _radius = 0.0f;
};

