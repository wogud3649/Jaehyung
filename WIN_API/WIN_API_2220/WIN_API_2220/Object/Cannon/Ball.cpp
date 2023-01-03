#include "framework.h"
#include "Ball.h"

Ball::Ball()
{
	_circle = make_shared<CircleCollider>(Vector2(0, 0), 5);
}

Ball::~Ball()
{
}

void Ball::Update()
{
	if (_isActive == false)
		return;

	//if (_delay >= 30.0f)
	//{
	//	_isActive = false;
	//	_delay = 0.0f;
	//}

	//_delay += 0.1f;

	//OutOfScreen();
	_circle->GetCenter().x += _dir.x * _speed.x;
	_circle->GetCenter().y += _dir.y * _speed.y;

	//_dir.y += GRAVITY * 0.01;
	if (_circle->GetCenter().y < 0 || _circle->GetCenter().y > WIN_HEIGHT)
		_dir.y *= -1;
	if (_circle->GetCenter().x < 0 || _circle->GetCenter().x > WIN_WIDTH)
		_dir.x *= -1;

	
	_circle->Update();
}

void Ball::Render(HDC hdc)
{
	if (_isActive == false)
		return;

	_circle->Render(hdc);
}

void Ball::Fire(Vector2 pos, Vector2 dir)
{
	_speed.y = 5.0f;
	_circle->GetCenter() = pos;
	_dir = dir.NormalVector2();
}

float Ball::Left()
{
	return _circle->GetCenter().x - _circle->GetRadius();
}

float Ball::Top()
{
	return _circle->GetCenter().y - _circle->GetRadius();
}

float Ball::Right()
{
	return _circle->GetCenter().x + _circle->GetRadius();
}

float Ball::Bottom()
{
	return _circle->GetCenter().y + _circle->GetRadius();
}

void Ball::OutOfScreen()
{
	if (Right() < 0 || Left() > WIN_WIDTH || Bottom() < 0 || Top() > WIN_HEIGHT)
		_isActive = false;
}
