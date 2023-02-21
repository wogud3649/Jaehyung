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
	for (int i = 0; i < _isDash.size(); i++)
	{
		if (_isDash[i])
		{
			_curDashCD[i] -= DELTA_TIME;
			if (_curDashCD[i] <= 0)
			{
				_curDashCD[i] = _maxDashCD;
				_isDash[i] = false;
			}
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
		if (_curState == State::ATTACKA || _curState == State::DASH)
			return;
		if (_direction == Direction::RIGHT)
			return;
		_direction = Direction::RIGHT;
		_sprites[_curSkul][_curState]->SetDirection(_direction);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		if (_curState == State::ATTACKA || _curState == State::DASH)
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
		if (_curState == State::ATTACKA || _curState == State::DASH)
			return;
		_bodyCol->GetTransform()->MoveX(_speed * DELTA_TIME);
		if (_curState == State::JUMP)
			return;
		_isGround = false;
		SetAction(State::WALK);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		if (_curState == State::ATTACKA || _curState == State::DASH)
			return;
		_bodyCol->GetTransform()->MoveX(-_speed * DELTA_TIME);
		if (_curState == State::JUMP)
			return;
		_isGround = false;
		SetAction(State::WALK);
	}
}

void Advanced_Player::Jump()
{
	if (KEY_DOWN('C'))
	{
		if (_curState == State::ATTACKA)
			return;
		if (_doubleJump)
			return;
		if (_isJump)
		{
			_doubleJump = true;
			SetAction(State::JUMP);
			_curJumpPower = _maxJumpPower;
			return;
		}
		_isGround = false;
		_isJump = true;
		SetAction(State::JUMP);
		_curJumpPower = _maxJumpPower;
	}
}

void Advanced_Player::Dash()
{
	if (KEY_DOWN('Z'))
	{
		if (_curState == State::DASH)
			return;
		auto iter = find_if(_isDash.begin(), _isDash.end(), [](const bool& a)->bool
			{
				return a == false;
			});
		if (iter == _isDash.end())
			return;
		(*iter) = true;
		_isGround = false;
		_curJumpPower = 0.0f;
		SetAction(State::DASH);
	}
}

void Advanced_Player::Fall()
{
	if (_isGround || _curState == State::DASH)
		return;

	_bodyCol->GetTransform()->MoveY(_curJumpPower * DELTA_TIME);
	_curJumpPower -= GRAVITY * GRAVITY * DELTA_TIME;
}

void Advanced_Player::Ground()
{
	_isGround = true;
	_isJump = false;
	_doubleJump = false;
	_curJumpPower = 0.0f;
}

void Advanced_Player::Beat()
{
}

void Advanced_Player::AttackA()
{
	if (KEY_DOWN('X'))
	{
		if (_curState == State::JUMP || _curState == State::ATTACKA)
			return;
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
	if (_curState == State::JUMP || _curState == State::ATTACKA || _curState == State::DASH)
		return;
	if (KEY_UP(VK_RIGHT) || KEY_UP(VK_LEFT))
		SetAction(State::IDLE);
}

void Advanced_Player::DashEnd()
{
	_curDashDistance = _maxDashDistance;
	SetAction(State::IDLE);
}

void Advanced_Player::AttackEnd()
{
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

	_actions[SkulType::HEADLESS][State::DASH]->SetCallBack(std::bind(&Advanced_Player::DashEnd, this));
	_actions[SkulType::HEADLESS][State::ATTACKA]->SetCallBack(std::bind(&Advanced_Player::AttackEnd, this));
}
