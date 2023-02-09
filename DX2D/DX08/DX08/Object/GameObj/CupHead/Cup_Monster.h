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

	void SetPlayer(shared_ptr<Cup_Advanced_Player> player);

	int& GetHp() { return _curHp; }
	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<RectCollider> GetCollider() { return _col; }

private:
	void CreatAction();

	shared_ptr<Cup_Monster_Bullet> SelectBullet();

	shared_ptr<Transform> _transform;
	shared_ptr<RectCollider> _col;

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;

	shared_ptr<Transform> _muzzle;
	int _maxHp = 10;
	int _curHp = _maxHp;

	bool _isAlive = true;

	vector<shared_ptr<Cup_Monster_Bullet>> _bullets;
	int _poolCount = 10;

	weak_ptr<Cup_Advanced_Player> _player;
};

