#pragma once
class Yggdrasil
{
public:
	Yggdrasil();
	~Yggdrasil();

	void Update();
	void Render();

	void SetTarget(shared_ptr<Advanced_Player> target) { _target = target; }

private:
	shared_ptr<Quad> _body;

	shared_ptr<Quad> _rightHand;
	shared_ptr<Quad> _leftHand;

	shared_ptr<CircleCollider> _headCol;
	shared_ptr<RectCollider> _rightBranchCol;
	shared_ptr<RectCollider> _leftBranchCol;
	shared_ptr<RectCollider> _handCol;

	float _maxHp = 1000.0f;
	float _curHp = _maxHp;

	float _attackCooldown = 3.0f;

	float maxDamage = 15.0f;
	float minDamage = 4.0f;

	weak_ptr<Advanced_Player> _target;
};

