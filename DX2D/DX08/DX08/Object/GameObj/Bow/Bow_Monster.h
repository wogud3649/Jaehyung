#pragma once
class Bow_Monster
{
public:
	Bow_Monster();
	~Bow_Monster();

	void Update();
	void Render();

	shared_ptr<CircleCollider>& GetCollider() { return _col; }

private:
	shared_ptr<Quad> _quad;
	shared_ptr<CircleCollider> _col;
};

