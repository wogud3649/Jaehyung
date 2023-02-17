#pragma once
class Floor
{
public:
	Floor();
	~Floor();

	void Update();
	void Render();

	shared_ptr<RectCollider> GetCollider() { return _col; }
private:
	shared_ptr<Quad> _floor;
	shared_ptr<RectCollider> _col;
};

