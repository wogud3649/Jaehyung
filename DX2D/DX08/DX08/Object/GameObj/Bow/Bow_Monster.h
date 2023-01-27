#pragma once
class Bow_Monster
{
public:
	Bow_Monster();
	~Bow_Monster();

	void Update();
	void Render();

	shared_ptr<CircleCollider>& GetCollider() { return _col; }
	int& GetHp() { return _hp; }

	void Damaged(int damage);
	void Revive();
	
private:
	shared_ptr<Quad> _quad;
	shared_ptr<CircleCollider> _col;
	
	int _maxHp = 100;
	int _hp = _maxHp;
	bool isActive = true;
};

