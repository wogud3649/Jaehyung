#pragma once
class Cup_Monster
{
public:
	Cup_Monster();
	~Cup_Monster();

	void Update();
	void Render();

	void Fire();

	void SetPlayer(shared_ptr<Cup_Advanced_Player> player);

	shared_ptr<Transform> GetTransform() { return _transform; }

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

	vector<shared_ptr<Cup_Monster_Bullet>> _bullets;
	int _poolCount = 10;

	weak_ptr<Cup_Advanced_Player> _player;

	float _shootDelay = 1.0f;
	float _shootTime = 0.0f;
};

