#pragma once
class Cup_Monster
{
public:
	Cup_Monster();
	~Cup_Monster();

	void Update();
	void Render();

	void EnAble();
	void DisAble();

	void Fire();
	void Damaged();
	void Revive();
	void Death();

	void SetTarget(shared_ptr<Cup_Advanced_Player> target);

	int& GetHp() { return _curHp; }
	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<RectCollider> GetCollider() { return _col; }
	shared_ptr<FilterSprite> GetSprite() { return _sprite; }

	vector<shared_ptr<Cup_Monster_Bullet>>& GetBullets() { return _bullets; }

private:
	void CreatAction();

	shared_ptr<Cup_Monster_Bullet> SelectBullet();

	shared_ptr<Transform> _transform;
	shared_ptr<RectCollider> _col;

	shared_ptr<FilterSprite> _sprite;
	shared_ptr<Action> _action;

	shared_ptr<Transform> _muzzle;
	int _maxHp = 1;
	int _curHp = _maxHp;

	bool isAlive = true;

	vector<shared_ptr<Cup_Monster_Bullet>> _bullets;
	int _poolCount = 10;

	weak_ptr<Cup_Advanced_Player> _target;
};

