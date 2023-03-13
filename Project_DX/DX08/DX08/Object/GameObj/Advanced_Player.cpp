#include "framework.h"
#include "Advanced_Player.h"

Advanced_Player::Advanced_Player()
{
	_attackCol = make_shared<CircleCollider>(50);
	_attackCol->GetTransform()->SetParent(_footCol->GetTransform());
	_attackCol->GetTransform()->MoveX(5);
	_attackCol->GetTransform()->MoveY(25);

	SetCallback();
}

Advanced_Player::~Advanced_Player()
{
}

void Advanced_Player::Update()
{
	_attackCol->Update();

	if (KEY_DOWN(VK_F2))
	{
		SetSkul(SkulType::SKUL);
	}
	if (KEY_DOWN(VK_F3))
	{
		SetSkul(SkulType::PIKE);
	}
	if (KEY_DOWN(VK_F4))
	{
		SetSkul(SkulType::SWORD);
	}

	SetIdle();
	Attack();
	Flip();
	Jump();
	Dash();
	Move();
	Fall();
	Skill();

	Player::Update();

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
		float distance = LERP(0, _curDashDistance, DELTA_TIME * 10.0f);
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

	if (_isInvincible)
	{
		_curInvincibleTime -= DELTA_TIME;
		if (_curInvincibleTime < 0.0f)
		{
			_isInvincible = false;
			_curInvincibleTime = _maxInvincibleTime;
		}
	}

	if (_isKnockBacked)
	{
		float distance = LERP(0.0f, _knockBackPower, DELTA_TIME * 6.0f);
		_knockBackPower -= distance;

		if (_knockBackRight)
			_footCol->GetTransform()->MoveX(distance);
		else
			_footCol->GetTransform()->MoveX(-distance);

		if (_knockBackPower <= 0.0f)
			_isKnockBacked = false;
	}

	if (_curState != State::ATTACKA && _curState != State::ATTACKB && _curState != State::JUMPATTACK)
		_attackCol->DeActivate();
}

void Advanced_Player::Render()
{
	Player::Render();

	_attackCol->Render();
}

void Advanced_Player::PostRender()
{
	ImGui::SliderFloat("PLAYER HP", &_curHp, 0, _maxHp);
	ImGui::SliderFloat("KnockBack", &_knockBackPower, 0, 9999);
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
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK || _curState == State::DASH || _curState == State::SKILL)
			return;
		if (_direction == Direction::RIGHT)
			return;
		_direction = Direction::RIGHT;
		_sprites[_curSkul][_curState]->SetDirection(_direction);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK || _curState == State::DASH || _curState == State::SKILL)
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
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK || _curState == State::DASH || _curState == State::SKILL)
			return;
		_footCol->GetTransform()->MoveX(_speed * DELTA_TIME);
		if (_curState == State::JUMP || _curState == State::FALLREPEAT || _curState == State::FALL)
			return;
		_isGround = false;
		SetAction(State::WALK);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK || _curState == State::DASH || _curState == State::SKILL)
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
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK || _curState == State::SKILL || _curState == State::DASH)
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
	if (_curState == State::DASH || _curState == State::ATTACKA || _curState == State::ATTACKB)
		return;

	_footCol->GetTransform()->MoveY(_curJumpPower * DELTA_TIME);
	_curJumpPower -= GRAVITY * GRAVITY * DELTA_TIME;
	
	if (_curJumpPower <= 0 && _curState != State::FALLREPEAT && _curState != State::JUMPATTACK && _curState != State::SKILL)
	{
		if (_curState == State::WALK && _curJumpPower >= -100.0f)
			return;
		if (_isGround && _curJumpPower >= -100.0f)
			return;
		
		SetAction(State::FALL);
	}
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

void Advanced_Player::Attack()
{
	if (KEY_DOWN('X'))
	{
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK || _curState == State::DASH || _curState == State::SKILL)
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

void Advanced_Player::Hit()
{
	_attackCol->DeActivate();
}

void Advanced_Player::Skill()
{
	if (KEY_DOWN('A'))
	{
		if (_curSkul == SkulType::HEADLESS)
			return;
		SetAction(State::SKILL);
	}
}

void Advanced_Player::Damaged(int damage, Direction dir)
{
	if (_isInvincible)
		return;
	_isInvincible = true;

	_isKnockBacked = true;
	_knockBackPower = 250.0f;
	if (dir == Direction::RIGHT)
		_knockBackRight = true;
	else
		_knockBackRight = false;

	_curHp -= damage;
}

void Advanced_Player::Dead()
{
}

void Advanced_Player::Revive()
{
}

void Advanced_Player::SetIdle()
{
	if (_curState == State::JUMP || _curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK || _curState == State::DASH || _curState == State::FALLREPEAT || _curState == State::FALL || _curState == State::SKILL)
		return;
	if (KEY_UP(VK_RIGHT) || KEY_UP(VK_LEFT))
		SetAction(State::IDLE);
}

void Advanced_Player::DashEnd()
{
	_curDashDistance = _maxDashDistance;
	SetAction(State::FALL);
}

void Advanced_Player::AttackMid()
{
	_attackCol->GetTransform()->Update();
	_attackCol->Activate();
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
	if (_curSkul == SkulType::SKUL)
	{
		_headOn = false;
		SetSkul(SkulType::HEADLESS);
	}
	else
	{
		SetAction(State::IDLE);
	}
}

void Advanced_Player::SetCallback()
{
	for (int i = 0; i < static_cast<int>(SkulType::SkulTypeSize); i++)
	{
		_actions[i][State::DASH]->SetCallBack(std::bind(&Advanced_Player::DashEnd, this));
		_actions[i][State::FALL]->SetCallBack(std::bind(&Advanced_Player::FallEnd, this));
		_actions[i][State::ATTACKA]->SetCallBack(std::bind(&Advanced_Player::AttackEnd, this));
		_actions[i][State::ATTACKB]->SetCallBack(std::bind(&Advanced_Player::AttackEnd, this));
		_actions[i][State::JUMPATTACK]->SetCallBack(std::bind(&Advanced_Player::AttackEnd, this));
	}
	_actions[SkulType::SKUL][State::ATTACKA]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this));
	_actions[SkulType::SKUL][State::ATTACKB]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this));
	_actions[SkulType::SKUL][State::JUMPATTACK]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this));

	_actions[SkulType::SKUL][State::SKILL]->SetCallBack(std::bind(&Advanced_Player::SkillEnd, this));

	_actions[SkulType::HEADLESS][State::ATTACKA]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this));
	_actions[SkulType::HEADLESS][State::ATTACKB]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this));
	_actions[SkulType::HEADLESS][State::JUMPATTACK]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this));

	_actions[SkulType::PIKE][State::SKILL]->SetCallBack(std::bind(&Advanced_Player::SkillEnd, this));

	_actions[SkulType::SWORD][State::SKILL]->SetCallBack(std::bind(&Advanced_Player::SkillEnd, this));
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