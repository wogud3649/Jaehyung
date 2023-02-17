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
		for (auto sprite : _sprites)
			sprite->SetDirection(Direction::RIGHT);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		for (auto sprite : _sprites)
			sprite->SetDirection(Direction::LEFT);
	}
}

void Advanced_Player::Move()
{
	if (KEY_PRESS(VK_RIGHT))
	{
		SetAction(State::WALK);
		_col->GetTransform()->MoveX(_speed * DELTA_TIME);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		SetAction(State::WALK);
		_col->GetTransform()->MoveX(-_speed * DELTA_TIME);
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
		float temp = 0.0f;
		while (temp < _dashTime)
		{
			float cur = 0;
			float end = 10;
			if (_sprites[0]->GetDirection() == Direction::LEFT)
				end = -end;
			_col->GetTransform()->MoveX(LERP(cur, end, _dashTime * DELTA_TIME));
			temp += DELTA_TIME;
		}
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
	SetAction(State::IDLE);
}
