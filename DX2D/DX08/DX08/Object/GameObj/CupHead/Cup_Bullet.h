#pragma once
class Cup_Bullet
{
public:
	Cup_Bullet();
	~Cup_Bullet();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _sprite->GetTransform()->GetPos() = pos; }
	void SetDirection(int dir);
	void Enable();

	shared_ptr<Transform> GetTransform() { return _sprite->GetTransform(); }
	bool GetActive() { return _isActive; }

	bool isActive;

private:
	void Init();
	void CreateAction();
	void Reset();

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;

	Vector2 _dir = { 0.0f,0.0f };
	float _speed = 500.0f;
	float _lifeTime = 2.0f;
	float _delay = 0.0f;

	bool _isActive = false;
};