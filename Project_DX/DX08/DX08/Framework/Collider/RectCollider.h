#pragma once
class CircleCollider;

class RectCollider : public Collider, public enable_shared_from_this<RectCollider>
{
public:
	friend CircleCollider;

	struct OBB_DESC
	{
		Vector2 position;
		Vector2 direction[2]; // 가로 세로 벡터
		float length[2]; // 가로 세로 길이
	};

	RectCollider(Vector2 size);
	~RectCollider();

	float Left() { return _transform->GetWorldPos().x - _size.x * 0.5f * _transform->GetWorldScale().x; }
	float Right() { return _transform->GetWorldPos().x + _size.x * 0.5f * _transform->GetWorldScale().x; }
	float Top() { return _transform->GetWorldPos().y + _size.y * 0.5f * _transform->GetWorldScale().y; }
	float Bottom() { return _transform->GetWorldPos().y - _size.y * 0.5f * _transform->GetWorldScale().y; }

	Vector2 GetWorldHalfSize();

	virtual void CreateData() override;

	virtual void Update() override;
	virtual void Render() override;

	virtual bool IsCollision(Vector2 pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other, bool isObb = false) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other, bool isObb = false) override;
	
	virtual HIT_RESULT Block(shared_ptr<CircleCollider> other);
	virtual HIT_RESULT Block(shared_ptr<RectCollider> other);
	virtual HIT_RESULT TopBlock(shared_ptr<CircleCollider> other);

	bool IsAABB(shared_ptr<RectCollider> other);
	bool IsAABB(shared_ptr<CircleCollider> other);

	bool IsOBB(shared_ptr<RectCollider> other);
	bool IsOBB(shared_ptr<CircleCollider> other);

	OBB_DESC GetOBB();

	float SeparateAxis(Vector2 separate, Vector2 e1, Vector2 e2);

private:
	void CreateVertices();

	Vector2 _size = { 0,0 };
};

