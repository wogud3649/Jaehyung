#pragma once
class Cannon
{
public:
	Cannon();
	~Cannon();

	void Update();
	void Render(HDC hdc);

private:
	shared_ptr<Collider> _body;
	shared_ptr<Barrel> _barrel;
	// 오브젝트 풀링
	vector<shared_ptr<Ball>> _balls;
	int _ballNum = 30;

	float _barrelLength = 60.0f;

	Vector2 _dir = { 1.0f, 0.0f };
	float _angle = 0.0f;
	float _power = 0.0f;
};