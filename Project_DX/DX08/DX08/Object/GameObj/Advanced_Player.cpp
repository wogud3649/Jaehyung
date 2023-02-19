#include "framework.h"
#include "Advanced_Player.h"

Advanced_Player::Advanced_Player()
{
}

Advanced_Player::~Advanced_Player()
{
}

void Advanced_Player::Update()
{
	Flip();
	Move();
	Jump();
	Dash();
	Fall();
	Attack();
	Skill();
	SetIdle();
	if (!_headOn)
	{
		if (_headDelay > 0.0f)
		{
			_headDelay -= DELTA_TIME;
		}
		if (_headDelay <= 0.0f)
		{
			_headDelay = 5.0f;
			_headOn = true;
			SetSkul(SkulType::SKUL);
		}
	}
	Player::Update();
}

void Advanced_Player::Render()
{
	Player::Render();
}

void Advanced_Player::EnAble()
{
}

void Advanced_Player::DisAble()
{
}

void Advanced_Player::Flip()
{
	if (KEY_PRESS(VK_RIGHT))
	{
		if (_direction == Direction::RIGHT)
			return;
		_direction = Direction::RIGHT;
		_sprites[_curSkul][_curState]->SetDirection(_direction);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		if (_direction == Direction::LEFT)
			return;
		_direction = Direction::LEFT;
		_sprites[_curSkul][_curState]->SetDirection(_direction);
	}
}

void Advanced_Player::Move()
{
	if (KEY_PRESS(VK_RIGHT))
	{
		SetAction(State::WALK);
		_bodyCol->GetTransform()->MoveX(_speed * DELTA_TIME);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		SetAction(State::WALK);
		_bodyCol->GetTransform()->MoveX(-_speed * DELTA_TIME);
	}
}

void Advanced_Player::Jump()
{
	if (KEY_DOWN('C'))
	{
		SetAction(State::JUMP);
	}
}

void Advanced_Player::Dash()
{
	if (KEY_DOWN('Z'))
	{
		SetAction(State::DASH);

		if (_direction == Direction::RIGHT)
			_bodyCol->GetTransform()->MoveX(100);
		if (_direction == Direction::LEFT)
			_bodyCol->GetTransform()->MoveX(-100);
	}
}

void Advanced_Player::Fall()
{
}

void Advanced_Player::Ground()
{
}

void Advanced_Player::Beat()
{
}

void Advanced_Player::Attack()
{
	if (KEY_DOWN('X'))
	{
		if (_curState == State::ATTACKA)
			SetAction(State::ATTACKB);
		else
			SetAction(State::ATTACKA);
	}
}

void Advanced_Player::Skill()
{
	if (KEY_DOWN('A'))
	{
		SetAction(State::SKILL);
		if (_headOn)
		{
			_headOn = false;
			SetSkul(SkulType::HEADLESS);
		}
	}
}

void Advanced_Player::Damaged()
{
}

void Advanced_Player::Dead()
{
}

void Advanced_Player::Revive()
{
}

void Advanced_Player::SetIdle()
{
	if (KEY_UP(VK_RIGHT) || KEY_UP(VK_LEFT) || KEY_UP('X') || KEY_UP('Z'))
		SetAction(State::IDLE);
}
