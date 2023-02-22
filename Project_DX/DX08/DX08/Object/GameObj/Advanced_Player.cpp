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
	Move();
	Flip();
	Jump();
	Dash();
	Attack();
	Fall();
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
			_footCol->GetTransform()->MoveX(distance);
		if (_direction == Direction::LEFT)
			_footCol->GetTransform()->MoveX(-distance);
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
	if (_attackB)
	{
		_curComboDuration -= DELTA_TIME;
		if (_curComboDuration < 0.0f)
		{
			_curComboDuration = _maxComboDuration;
			_attackB = false;
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
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK || _curState == State::DASH)
			return;
		if (_direction == Direction::RIGHT)
			return;
		_direction = Direction::RIGHT;
		_sprites[_curSkul][_curState]->SetDirection(_direction);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK || _curState == State::DASH)
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
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK || _curState == State::DASH)
			return;
		_footCol->GetTransform()->MoveX(_speed * DELTA_TIME);
		if (_curState == State::JUMP || _curState == State::FALLREPEAT || _curState == State::FALL)
			return;
		_isGround = false;
		SetAction(State::WALK);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK || _curState == State::DASH)
			return;
		_footCol->GetTransform()->MoveX(-_speed * DELTA_TIME);
		if (_curState == State::JUMP || _curState == State::FALLREPEAT || _curState == State::FALL)
			return;
		_isGround = false;
		SetAction(State::WALK);
	}
}

void Advanced_Player::Jump()
{
	if (KEY_DOWN('C'))
	{
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK)
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
	if (_isGround || _curState == State::DASH || _curState == State::ATTACKA || _curState == State::ATTACKB)
		return;

	_footCol->GetTransform()->MoveY(_curJumpPower * DELTA_TIME);
	_curJumpPower -= GRAVITY * GRAVITY * DELTA_TIME;
	
	if (_curJumpPower <= 0 && _curState != State::FALLREPEAT && _curState != State::WALK && _curState != State::JUMPATTACK)
		SetAction(State::FALL);
}

void Advanced_Player::Ground()
{
	_isGround = true;
	_isJump = false;
	_doubleJump = false;
	_curJumpPower = 0.0f;
	if (_curState == FALL || _curState == FALLREPEAT || _curState == JUMPATTACK)
		SetAction(State::IDLE);
}

void Advanced_Player::Beat()
{
	_curJumpPower = 0.0f;
}

void Advanced_Player::Attack()
{
	if (KEY_DOWN('X'))
	{
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK || _curState == State::DASH)
			return;

		if (_curState == State::JUMP || _curState == State::FALLREPEAT || _curState == State::FALL)
		{
			SetAction(State::JUMPATTACK);
		}
		else if (_attackB)
		{
			_attackB = false;
			_curComboDuration = _maxComboDuration;
			SetAction(State::ATTACKB);
		}
		else
		{
			_attackB = true;
			SetAction(State::ATTACKA);
		}
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
	if (_curState == State::JUMP || _curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK || _curState == State::DASH || _curState == State::FALLREPEAT || _curState == State::FALL)
		return;
	if (KEY_UP(VK_RIGHT) || KEY_UP(VK_LEFT))
		SetAction(State::IDLE);
}

void Advanced_Player::DashEnd()
{
	_curDashDistance = _maxDashDistance;
	SetAction(State::FALL);
}

void Advanced_Player::AttackEnd()
{
	if (_isGround)
		SetAction(State::IDLE);
	else
		SetAction(State::FALL);
}

void Advanced_Player::FallEnd()
{
	SetAction(State::FALLREPEAT);
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
	_actions[SkulType::SKUL][State::ATTACKB]->SetCallBack(std::bind(&Advanced_Player::AttackEnd, this));
	_actions[SkulType::SKUL][State::JUMPATTACK]->SetCallBack(std::bind(&Advanced_Player::AttackEnd, this));
	_actions[SkulType::SKUL][State::FALL]->SetCallBack(std::bind(&Advanced_Player::FallEnd, this));

	_actions[SkulType::HEADLESS][State::DASH]->SetCallBack(std::bind(&Advanced_Player::DashEnd, this));
	_actions[SkulType::HEADLESS][State::ATTACKA]->SetCallBack(std::bind(&Advanced_Player::AttackEnd, this));
	_actions[SkulType::HEADLESS][State::ATTACKB]->SetCallBack(std::bind(&Advanced_Player::AttackEnd, this));
	_actions[SkulType::HEADLESS][State::JUMPATTACK]->SetCallBack(std::bind(&Advanced_Player::AttackEnd, this));
	_actions[SkulType::HEADLESS][State::FALL]->SetCallBack(std::bind(&Advanced_Player::FallEnd, this));
}

void Advanced_Player::SetAction(State state)
{
	_curState = state;
	if (_curState == _oldState)
		return;

	_sprites[_curSkul][_curState]->SetDirection(_direction);
	_actions[_curSkul][_curState]->Play();
	_actions[_curSkul][_oldState]->Reset();
	_oldState = _curState;
}

void Advanced_Player::SetSkul(SkulType skulType)
{
	_curSkul = skulType;
	if (_curSkul == _oldSkul)
		return;
	if (_curState != State::IDLE)
		_curState = State::IDLE;

	_sprites[_curSkul][_curState]->SetDirection(_direction);
	_actions[_curSkul][_curState]->Play();
	_actions[_oldSkul][_oldState]->Reset();
	_oldState = _curState;
	_oldSkul = _curSkul;
}