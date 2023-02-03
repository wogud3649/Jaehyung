#include "framework.h"
#include "Cup_Advanced_Player.h"

Cup_Advanced_Player::Cup_Advanced_Player()
{
	//for (int i = 0; i < _poolCount; i++)
	//{
	//	shared_ptr<Cup_Bullet> bullet = make_shared<Cup_Bullet>();
	//	bullet->isActive = false;
	//	_bullets.emplace_back(bullet);
	//}

	//_muzzle = make_shared<Transform>();
	//_muzzle->SetParent(_transform);
	//_muzzle->GetPos().x += 50;
}

Cup_Advanced_Player::~Cup_Advanced_Player()
{
}

void Cup_Advanced_Player::Update()
{
	//for (auto bullet : _bullets)
	//	bullet->Update();
	
	//Shot();

	Cup_Player::Update();
}

void Cup_Advanced_Player::Render()
{
	Cup_Player::Render();

	//for (auto bullet : _bullets)
	//	bullet->Render();
}

void Cup_Advanced_Player::Shot()
{
	//if (KEY_DOWN(VK_LBUTTON))
	//{
	//	SetAction(State::CUP_AIM_STRAIGHT_SHOT);
	//	shared_ptr<Cup_Bullet> bullet = SelectBullet();
	//	Vector2 dir;

	//	if (_isRight)
	//	{
	//		_muzzle->GetPos().x = 50;
	//		dir = Vector2(1, 0);
	//	}
	//	else
	//	{
	//		_muzzle->GetPos().x = -50;
	//		dir = Vector2(-1, 0);
	//	}

	//	bullet->SetPosition(_muzzle->GetPos());
	//	bullet->isActive = true;
	//	bullet->Enable();
	//}
}

shared_ptr<Cup_Bullet> Cup_Advanced_Player::SelectBullet()
{
	for (auto bullet : _bullets)
	{
		if (bullet->isActive == false)
		{
			return bullet;
		}
	}
}
