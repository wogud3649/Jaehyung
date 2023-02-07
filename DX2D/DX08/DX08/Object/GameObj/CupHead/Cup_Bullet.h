#pragma once
class Cup_Bullet
{
public:
	Cup_Bullet();
	~Cup_Bullet();

	void Update();
	void Render();

	void SetPostion(Vector2 pos) { _sprite->GetTransform()->GetPos() = pos; }
	void Fire(Vector2 dir);

	bool isActive;
private:
	void CreateAction();

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;

	float _speed = 200.0f;
	Vector2 _direction;

	float _delay = 0.0f;
	float _lifeTime = 2.0f;
};

