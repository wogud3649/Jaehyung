#pragma once
class Ball
{
public:
	Ball();
	~Ball();

	void Update();
	void Render(HDC hdc);

	float Left();
	float Top();
	float Right();
	float Bottom();

	void Fire(Vector2 pos, Vector2 dir);

	void OutOfScreen();
	bool _isActive = false;
private:
	shared_ptr<CircleCollider> _circle;

	Vector2 _dir = { 0.0f, 0.0f };
	Vector2 _speed = { 5.0f, 5.0f };

	float _delay = 0.0f;
};

