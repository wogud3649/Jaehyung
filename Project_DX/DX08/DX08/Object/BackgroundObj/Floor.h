#pragma once
class Floor
{
public:
	Floor();
	~Floor();

	void Update();
	void Render();

	shared_ptr<RectCollider> GetCollider() { return _col; }
	HIT_RESULT GetHIT_RESULT(shared_ptr<CircleCollider> other) { return _col->Block(other); }

private:
	shared_ptr<Quad> _floor;
	shared_ptr<RectCollider> _col;
};

