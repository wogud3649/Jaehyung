#include "framework.h"
#include "Cannon.h"

Cannon::Cannon()
{
	_body = make_shared<CircleCollider>(Vector2(CENTER_X, CENTER_Y), 30.0f);
	_barrel = make_shared<Barrel>();
	_balls.reserve(_ballNum);
	_balls.resize(_ballNum);
	for (auto& ball : _balls)
		ball = make_shared<Ball>();
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	if (GetAsyncKeyState(VK_RIGHT))
	{
		_body->GetCenter().x += 2.0f;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		_body->GetCenter().x -= 2.0f;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		_angle += 0.1f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		_angle -= 0.1f;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x1001)
	{
		auto ball = std::find_if(_balls.begin(), _balls.end(), [](const shared_ptr<Ball>& ball)->bool
			{
				if (ball->_isActive)
					return false;
				return true;
			});

		Vector2 direction = _barrel->GetDirection();
		if (ball != _balls.end())
		{
			(*ball)->_isActive = true;
			(*ball)->Fire(_barrel->GetEnd(), direction);
		}
		//for (auto& ball : _balls)
		//{
		//	if (ball->_isActive == false)
		//	{
		//		ball->_isActive = true;
		//		Vector2 direction = _barrel->GetDirection();
		//		ball->Fire(_barrel->GetEnd(), direction);
		//		break;
		//	}
		//}
	}

	_dir.x = cos(_angle);
	_dir.y = -sin(_angle);

	_barrel->SetStart(_body->GetCenter());
	Vector2 barrelEnd = _dir * _barrelLength;
	_barrel->SetEnd(_body->GetCenter() + barrelEnd);

	_body->Update();
	_barrel->Update();
	for (auto& ball : _balls)
		ball->Update();
}

void Cannon::Render(HDC hdc)
{
	_barrel->Render(hdc);
	_body->Render(hdc);
	for (auto& ball : _balls)
		ball->Render(hdc);
}
