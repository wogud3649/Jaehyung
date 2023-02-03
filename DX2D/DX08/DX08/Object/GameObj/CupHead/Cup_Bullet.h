#pragma once
class Cup_Bullet
{
public:
	Cup_Bullet();
	~Cup_Bullet();

	void Update();
	void Render();

	void Fire();

private:
	void Init();

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;

	float _speed = 300.0f;

	bool _isActive = false;
};