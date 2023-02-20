#include "framework.h"
#include "Advanced_Player.h"

Advanced_Player::Advanced_Player()
{
	SetCallback();
}

Advanced_Player::~Advanced_Player()
{
}

void Advanced_Player::Update()
{
	if (KEY_UP(VK_RIGHT) || KEY_UP(VK_LEFT))
		SetIdle();
	Flip();
	Move();
	Jump();
	Dash();
	Fall();
	AttackA();
	Skill();
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
	if (_curState == State::DASH)
	{
		float distance = LERP(0, _curDashDistance, DELTA_TIME);
		_curDashDistance -= distance;
		if (_direction == Direction::RIGHT)
			_bodyCol->GetTransform()->MoveX(distance);
		if (_direction == Direction::LEFT)
			_bodyCol->GetTransform()->MoveX(-distance);
	}
	if (_dashAble == false)
	{
		_curDashCD -= DELTA_TIME;
		if (_curDashCD <= 0)
		{
			_curDashCD = _maxDashCD;
			_dashAble = true;
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
		if (_isAttacking)
			return;
		if (_direction == Direction::RIGHT)
			return;
		_direction = Direction::RIGHT;
		_sprites[_curSkul][_curState]->SetDirection(_direction);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		if (_isAttacking)
			return;
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
		if (_isAttacking)
			return;
		_bodyCol->GetTransform()->MoveX(_speed * DELTA_TIME);
		if (_isJump)
			return;
		_isGround = false;
		SetAction(State::WALK);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		if (_isAttacking)
			return;
		_bodyCol->GetTransform()->MoveX(-_speed * DELTA_TIME);
		if (_isJump)
			return;
		_isGround = false;
		SetAction(State::WALK);
	}
}

void Advanced_Player::Jump()
{
	if (KEY_DOWN('C'))
	{
		if (_isAttacking)
			return;
		if (_isJump)
			return;
		_isGround = false;
		_isJump = true;
		SetAction(State::JUMP);
		_curJumpPower = _maxJumpPower;
	}
}

void Advanced_Player::Dash()
{
	if (KEY_DOWN('Z') && _dashAble)
	{
		_curJumpPower = 0.0f;
		SetAction(State::DASH);
		_isDash = true;
		_isGround = false;
		_dashAble = false;
	}
}

void Advanced_Player::Fall()
{
	if (_isGround || _isDash)
		return;

	_bodyCol->GetTransform()->MoveY(_curJumpPower * DELTA_TIME);
	_curJumpPower -= GRAVITY * GRAVITY * DELTA_TIME;
}

void Advanced_Player::Ground()
{
	_isJump = false;
	_curJumpPower = 0.0f;
	_isGround = true;
}

void Advanced_Player::Beat()
{
}

void Advanced_Player::AttackA()
{
	if (KEY_DOWN('X'))
	{
		if (_isJump)
			return;
		_isAttacking = true;
		SetAction(State::ATTACKA);
	}
}

void Advanced_Player::Skill()
{
	if (KEY_DOWN('A'))
	{
		SetAction(State::SKILL);
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
	if (_isJump || _isAttacking)
		return;
	SetAction(State::IDLE);
}

void Advanced_Player::DashEnd()
{
	_isDash = false;
	_curDashDistance = _maxDashDistance;
	SetAction(State::IDLE);
}

void Advanced_Player::AttackEnd()
{
	_isAttacking = false;
	SetAction(State::IDLE);
}

void Advanced_Player::SkillEnd()
{
	_headOn = false;
	SetSkul(SkulType::HEADLESS);
}

void Advanced_Player::SetCallback()
{
	_actions[SkulType::SKUL][State::DASH]->SetCallBack(std::bind(&Advanced_Player::DashEnd, this));
	_actions[SkulType::SKUL][State::SKILL]->SetCallBack(std::bind(&Advanced_Player::SkillEnd, this));
	_actions[SkulType::SKUL][State::ATTACKA]->SetCallBack(std::bind(&Advanced_Player::AttackEnd, this));
}
