#pragma once
class CircleCollider : public Collider, public enable_shared_from_this<CircleCollider>
{
public:
	CircleCollider(float radius);
	~CircleCollider();

	virtual void CreateData() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual bool IsCollision(Vector2 pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other, bool isObb = false) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other, bool isObb = false) override;

	virtual bool Block(shared_ptr<CircleCollider> other);
	virtual bool Block(shared_ptr<RectCollider> other);

	float WorldRadius();

private:
	void CreateVertices();

	float _radius = 0.0f;
};

