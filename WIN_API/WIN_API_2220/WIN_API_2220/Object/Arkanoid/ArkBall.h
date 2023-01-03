#pragma once
class ArkBall
{
public:
	ArkBall();
	~ArkBall();

	void Update();
	void Render(HDC hdc);

	shared_ptr<CircleCollider>& GetCollider() { return _circle; }
	Vector2& GetCenter() { return _circle->GetCenter(); }
	Vector2& GetDirection() { return _dir; }
	float GetRadius() { return _radius; }
	float GetSpeed() { return _speed; }
	bool& GetFired() { return _fired; }
	bool& GetActive() { return _circle->_isActive; }

	void Reflection();
private:
	shared_ptr<CircleCollider> _circle;
	float _radius = 10.0f;

	Vector2 _dir = { 0.0f, -1.0f };
	float _speed = 10.0f;
	bool _fired = false;
};

