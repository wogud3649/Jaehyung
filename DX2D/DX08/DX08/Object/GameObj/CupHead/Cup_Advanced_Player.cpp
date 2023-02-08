#include "framework.h"
#include "Cup_Advanced_Player.h"

Cup_Advanced_Player::Cup_Advanced_Player()
{
	for (int i = 0; i < _poolCount; i++)
	{
		shared_ptr<Cup_Bullet> bullet = make_shared<Cup_Bullet>();
		bullet->isActive = false;
		_bullets.push_back(bullet);
	}

	_actions[State::CUP_SHOT]->SetCallBack(std::bind(&Cup_Advanced_Player::EndShot, this));
	_actions[State::CUP_JUMP]->SetCallBack(std::bind(&Cup_Advanced_Player::Ground, this));

	_muzzle = make_shared<Transform>();
	_muzzle->SetParent(_col->GetTransform());
	_muzzle->GetPos().x = 50;
}

Cup_Advanced_Player::~Cup_Advanced_Player()
{
}

void Cup_Advanced_Player::Update()
{
	for (auto bullet : _bullets)
		bullet->Update();
	
	Shot();
	Jump();

	if (_curState != State::CUP_SHOT)
		_col->GetTransform()->GetPos().y += _jumpPower * DELTA_TIME;

	Cup_Player::Update();
}

void Cup_Advanced_Player::Render()
{
	Cup_Player::Render();

	for (auto bullet : _bullets)
		bullet->Render();
}

void Cup_Advanced_Player::Shot()
{
	if (_curState == State::CUP_JUMP || _curState == State::CUP_SHOT)
		return;

	if (KEY_DOWN(VK_LBUTTON))
	{
		_isShooting = true;
		SetAction(State::CUP_SHOT);
		shared_ptr<Cup_Bullet> bullet = SelectBullet();
		Vector2 dir;

		if (_isRight)
		{
			_muzzle->GetPos().x = 50;
			dir = Vector2(1, 0);
		}
		else
		{
			_muzzle->GetPos().x = -50;
			dir = Vector2(-1, 0);
		}

		bullet->SetPostion(_muzzle->GetWorldPos());
		bullet->isActive = true;
		bullet->Fire(dir);
	}
}

void Cup_Advanced_Player::EndShot()
{
	SetAction(CUP_IDLE);
	_isShooting = false;
}

void Cup_Advanced_Player::Jump()
{
	if (_curState == State::CUP_SHOT || _curState == State::CUP_JUMP)
		return;
	if (KEY_DOWN(VK_SPACE))
	{
		SetAction(State::CUP_JUMP);
		_jumpPower = _maxJumpPower;
	}
}

void Cup_Advanced_Player::Ground()
{
	if (_jumpPower < 0)
	{
		if (_curState == State::CUP_JUMP)
			SetAction(State::CUP_IDLE);
		_jumpPower = 0.0f;
	}
}

void Cup_Advanced_Player::Falling()
{
	_jumpPower -= GRAVITY * GRAVITY * DELTA_TIME;
}

void Cup_Advanced_Player::Beat()
{
	_jumpPower *= -1;
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
