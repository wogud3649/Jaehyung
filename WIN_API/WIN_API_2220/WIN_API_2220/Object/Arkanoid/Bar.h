#pragma once
class Bar
{
public:
	Bar();
	~Bar();

	void Update();
	void Render(HDC hdc);

	shared_ptr<ArkBall>& GetBallInfo() { return _arkBall; }
	int GetLife() { return _life; }

	void Fall();
	void Reset();

private:
	shared_ptr<RectCollider> _rectangle;
	Vector2 _size = { 150, 30 };

	shared_ptr<ArkBall> _arkBall;

	int _life = 3;
};