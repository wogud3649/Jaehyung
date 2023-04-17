#pragma once
class Slot
{
public:
	Slot();
	~Slot();

	void Update();
	void Render();

	shared_ptr<RectCollider> GetCollider() { return _col; }
	bool IsCollision(Vector2 pos) { return _col->IsCollision(pos).isHit; }

private:
	shared_ptr<RectCollider> _col;
};