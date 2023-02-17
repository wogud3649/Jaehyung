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
		for (auto sprite : _sprites[_curSkul])
			sprite->SetDirection(Direction::RIGHT);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		for (auto sprite : _sprites[_curSkul])
			sprite->SetDirection(Direction::LEFT);
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

		_bodyCol->GetTransform()->MoveX(100);
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

void Advanced_Player::Skill()
{
	if (KEY_DOWN(VK_F1))
	{
		if (_curSkul == SkulType::SKUL)
			SetSkul(SkulType::HEADLESS);
	}
	if (KEY_DOWN(VK_F2))
	{
		SetSkul(SkulType::SKUL);
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
	SetAction(State::IDLE);
}
