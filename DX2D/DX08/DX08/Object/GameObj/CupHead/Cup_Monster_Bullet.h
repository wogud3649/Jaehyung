#pragma once
class Cup_Monster_Bullet
{
public:
	Cup_Monster_Bullet();
	~Cup_Monster_Bullet();

	void Update();
	void Render();

	void EnAble();
	void DisAble();

	void SetPostion(Vector2 pos) { _sprite->GetTransform()->GetPos() = pos; }
	void SetTarget(shared_ptr<Cup_Advanced_Player> target) { _target = target; }
	void Fire();

	bool isActive = false;
private:
	void CreateAction();

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;

	shared_ptr<CircleCollider> _col;

	float _speed = 600.0f;
	Vector2 _direction;

	float _delay = 0.0f;
	float _lifeTime = 2.0f;

	weak_ptr<Cup_Advanced_Player> _target;
};

