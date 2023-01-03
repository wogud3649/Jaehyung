#include "framework.h"
#include "Bar.h"

Bar::Bar()
{
	_rectangle = make_shared<RectCollider>(Vector2(WIN_WIDTH / 2, WIN_HEIGHT - 100), _size);
	_arkBall = make_shared<ArkBall>();
}

Bar::~Bar()
{
}

void Bar::Update()
{
	if (GetAsyncKeyState(VK_RIGHT))
		_rectangle->GetCenter().x += _arkBall->GetSpeed();
	if (GetAsyncKeyState(VK_LEFT))
		_rectangle->GetCenter().x -= _arkBall->GetSpeed();

	if (GetAsyncKeyState(VK_SPACE))
		_arkBall->GetFired() = true;

	if (_arkBall->GetFired() == false)
		_arkBall->GetCenter() = Vector2(_rectangle->GetCenter().x, _rectangle->GetCenter().y-(_size.y/2)-_arkBall->GetRadius());
	
	if (_arkBall->GetActive() == false)
		Reset();

	if (_arkBall->GetFired())
	{
		if (_rectangle->IsCollision(_arkBall->GetCollider()))
		{
			_arkBall->GetDirection() = (_arkBall->GetCenter() - _rectangle->GetCenter()).NormalVector2();
		}
	}

	Fall();

	_rectangle->Update();
	_arkBall->Update();
}

void Bar::Render(HDC hdc)
{
	_rectangle->Render(hdc);
	_arkBall->Render(hdc);
}

void Bar::Fall()
{
	if (_arkBall->GetCenter().y > WIN_HEIGHT)
	{
		_arkBall->GetFired() = false;
		_arkBall->GetActive() = false;
		_life--;
	}
}

void Bar::Reset()
{
	if (_life > 0)
	{
		_arkBall->GetCenter() = Vector2(_rectangle->GetCenter().x, _rectangle->GetCenter().y - (_size.y / 2) - _arkBall->GetRadius());
		_arkBall->GetActive() = true;
	}
}