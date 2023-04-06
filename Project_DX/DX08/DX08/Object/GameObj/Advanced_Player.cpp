#include "framework.h"
#include "Advanced_Player.h"

Advanced_Player::Advanced_Player()
{
	_attackCol = make_shared<CircleCollider>(50);
	_attackCol->GetTransform()->SetParent(_footCol->GetTransform());
	_attackCol->GetTransform()->MoveX(5);
	_attackCol->GetTransform()->MoveY(25);
	_attackCol->DeActivate();

	_proj = make_shared<Quad>(L"Resources/Texture/SKUL/Head.png", Vector2(1,1));
	_proj->SetPS(ADD_PS(L"Shader/LRTexturePixelShader.hlsl"));
	_proj->Update();
	_projCol = make_shared<CircleCollider>(_proj->GetSize().y * 0.7f);
	_projCol->GetTransform()->SetParent(_proj->GetTransform());
	_projCol->DeActivate();

	_reverseBuffer = make_shared<ReverseBuffer>();

	SetCallback();
}

Advanced_Player::~Advanced_Player()
{
}

void Advanced_Player::Update()
{
	_reverseBuffer->Update();
	_attackCol->Update();
	_projCol->Update();

	SetIdle();
	Attack();
	Flip();
	Jump();
	Dash();
	Move();
	Fall();
	Skill();
	Bungee();

	Player::Update();

	if (!_isHeadOn)
	{
		if (_headDelay > 0.0f)
		{
			_headDelay -= DELTA_TIME;
		}
		if (_headDelay <= 0.0f)
		{
			_headDelay = _maxHeadDelay;
			_isHeadOn = true;
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

	if (_isAttackB)
	{
		_curComboDuration -= DELTA_TIME;
		if (_curComboDuration < 0.0f)
		{
			_curComboDuration = _maxComboDuration;
			_isAttackB = false;
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

		if (_isKnockBackRight)
			_footCol->GetTransform()->MoveX(distance);
		else
			_footCol->GetTransform()->MoveX(-distance);

		if (_knockBackPower <= 0.0f)
			_isKnockBacked = false;
	}

	if (_isProjFired)
	{
		_curProjCD -= DELTA_TIME;
		_proj->Update();
		if (_curProjCD < 0.0f)
		{
			_isProjFired = false;
			_curProjCD = _maxProjCD;
		}
		if (_projCol->GetActive())
		{
			if (_reverseBuffer->_data.reverse == 0)
				_proj->GetTransform()->MoveX(_projSpeed * DELTA_TIME);
			else
				_proj->GetTransform()->MoveX(-_projSpeed * DELTA_TIME);
		}
	}

	if (_isBungee)
	{
		_curBungeeCD -= DELTA_TIME;
		if (_curBungeeCD < 0.0f)
		{
			_curBungeeCD = _maxBungeeCD;
			_isBungee = false;
		}
	}
}

void Advanced_Player::Render()
{
	_reverseBuffer->SetPSBuffer(2);

	Player::Render();

	if (_projCol->GetActive())
	{
		_proj->Render();
	}

	_attackCol->Render();
	_projCol->Render();
}

void Advanced_Player::PostRender()
{
	ImGui::SliderFloat("PLAYER HP", &_curHp, 0, _maxHp);
	ImGui::SliderFloat("jumpPower", &_curJumpPower, 0, _maxJumpPower);
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
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::DASH || _curState == State::SKILL)
			return;
		_footCol->GetTransform()->MoveX(_speed * DELTA_TIME);
		if (_curState == State::JUMP || _curState == State::JUMPATTACK || _curState == State::FALLREPEAT || _curState == State::FALL)
			return;
		_isGround = false;
		SetAction(State::WALK);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::DASH || _curState == State::SKILL)
			return;
		_footCol->GetTransform()->MoveX(-_speed * DELTA_TIME);
		if (_curState == State::JUMP || _curState == State::JUMPATTACK || _curState == State::FALLREPEAT || _curState == State::FALL)
			return;

		_isGround = false;
		SetAction(State::WALK);
	}
}

void Advanced_Player::Jump()
{
	if (KEY_DOWN('C') && KEY_PRESS(VK_DOWN) == false)
	{
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK || _curState == State::SKILL || _curState == State::DASH)
			return;
		if (_isDoubleJump)
			return;

		if (_isJump)
		{
			_isDoubleJump = true;
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

void Advanced_Player::Bungee()
{
	if (KEY_PRESS(VK_DOWN) && KEY_DOWN('C'))
	{
		_isBungee = true;
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
		_isDodge = true;
	}
}

void Advanced_Player::Fall()
{
	if (_curState == State::DASH || _curState == State::ATTACKA || _curState == State::ATTACKB)
		return;

	_footCol->GetTransform()->MoveY(_curJumpPower * DELTA_TIME);
	_curJumpPower -= GRAVITY * GRAVITY * DELTA_TIME;
	if (_curJumpPower < -950.0f)
		_curJumpPower = -950.0f;
	
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
	_isDoubleJump = false;
	_curJumpPower = 0.0f;
	if (_curState == FALL || _curState == FALLREPEAT || _curState == JUMPATTACK)
		SetAction(State::IDLE);
}

void Advanced_Player::Bounce()
{
	_isGround = false;
	_isJump = false;
	_isDoubleJump = false;
	_curJumpPower = _maxJumpPower;
	if (_curState == FALL || _curState == FALLREPEAT || _curState == JUMPATTACK)
		SetAction(State::JUMP);
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
		else if (_isAttackB)
		{
			_isAttackB = false;
			_curComboDuration = _maxComboDuration;
			SetAction(State::ATTACKB);
		}
		else
		{
			_isAttackB = true;
			SetAction(State::ATTACKA);
		}
	}
}

void Advanced_Player::AttackHit()
{
	_attackCol->DeActivate();
}

void Advanced_Player::Skill()
{
	if (KEY_DOWN('A'))
	{
		if (_isProjFired)
			return;
		SetAction(State::SKILL);
		_isProjFired = true;
		_proj->GetTransform()->SetPos(_bodyCol->GetTransform()->GetWorldPos());
		_projCol->GetTransform()->UpdateSRT();
		_projCol->Activate();

		if (_direction == Direction::RIGHT)
			_reverseBuffer->_data.reverse = 0;
		else
			_reverseBuffer->_data.reverse = 1;
	}
}

void Advanced_Player::SkillHit()
{
	_headDelay = _maxHeadDelay;
	_isHeadOn = true;
	SetSkul(SkulType::SKUL);
	_projCol->DeActivate();
	_footCol->GetTransform()->SetPos(_proj->GetTransform()->GetWorldPos());
}

void Advanced_Player::Damaged(int damage, Direction dir)
{
	if (_isInvincible || _isDodge)
		return;

	_isInvincible = true;

	_isKnockBacked = true;
	_knockBackPower = 250.0f;
	if (dir == Direction::RIGHT)
		_isKnockBackRight = true;
	else
		_isKnockBackRight = false;

	_curHp -= damage;
}

void Advanced_Player::Dead()
{
}

void Advanced_Player::Revive()
{
}

float Advanced_Player::GetAttackDamage()
{
	int ad = (rand() % (_maxAttackDamage - _minAttackDamage) + _minAttackDamage);
	ad += _statAttributes.ad;

	int temp = rand() % 100;
	if (temp < _critPercent + _statAttributes.crp)
		ad *= 2;

	return ad;
}

float Advanced_Player::GetProjDamage()
{
	int ap = (rand() % (_maxProjDamage - _minProjDamage) + _minProjDamage);
	ap += _statAttributes.ap;

	int temp = rand() % 100;
	if (temp < _critPercent + _statAttributes.crp)
		ap *= 2;
	
	return ap;
}

void Advanced_Player::SetEquipStats(StatAttributes stats)
{
	_statAttributes = stats;

	_maxHp = _baseMaxHp + _statAttributes.hp;
	_def = _baseDef + _statAttributes.def;
	_critPercent = _baseCrp + _statAttributes.crp;
	_maxHeadDelay = _baseScd * ((float)(361 - _statAttributes.scd) / 100); // TODO :
	//_maxProjCD = _baseScd * (
	_maxChangeCD = _baseCcd * ((float)(100 - _statAttributes.ccd) / 100);
}

void Advanced_Player::Switch()
{
	vector<ItemInfo> data = INVENTORY->GetEquipedSkulInfo();

	if (data.size() > 1)
	{

	}
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
	_isDodge = false;
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

void Advanced_Player::AttackColEnd()
{
	_attackCol->DeActivate();
}

void Advanced_Player::FallEnd()
{
	SetAction(State::FALLREPEAT);
}

void Advanced_Player::SkillEnd()
{
	if (_curSkul == SkulType::SKUL && _projCol->GetActive())
	{
		_isHeadOn = false;
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
	_actions[SkulType::SKUL][State::ATTACKA]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this), 2);
	_actions[SkulType::SKUL][State::ATTACKA]->SetMidCallBack(std::bind(&Advanced_Player::AttackColEnd, this), 3);
	_actions[SkulType::SKUL][State::ATTACKB]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this), 1);
	_actions[SkulType::SKUL][State::ATTACKB]->SetMidCallBack(std::bind(&Advanced_Player::AttackColEnd, this), 2);
	_actions[SkulType::SKUL][State::JUMPATTACK]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this), 1);
	_actions[SkulType::SKUL][State::JUMPATTACK]->SetMidCallBack(std::bind(&Advanced_Player::AttackColEnd, this), 2);

	_actions[SkulType::SKUL][State::SKILL]->SetCallBack(std::bind(&Advanced_Player::SkillEnd, this));

	_actions[SkulType::HEADLESS][State::ATTACKA]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this), 2);
	_actions[SkulType::HEADLESS][State::ATTACKA]->SetMidCallBack(std::bind(&Advanced_Player::AttackColEnd, this), 3);
	_actions[SkulType::HEADLESS][State::ATTACKB]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this), 1);
	_actions[SkulType::HEADLESS][State::ATTACKB]->SetMidCallBack(std::bind(&Advanced_Player::AttackColEnd, this), 2);
	_actions[SkulType::HEADLESS][State::JUMPATTACK]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this), 1);
	_actions[SkulType::HEADLESS][State::JUMPATTACK]->SetMidCallBack(std::bind(&Advanced_Player::AttackColEnd, this), 2);

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
	_sprites[_curSkul][_oldState]->SetActionClip(_actions[_curSkul][_oldState]->GetCurClip());
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
	_sprites[_oldSkul][_oldState]->SetActionClip(_actions[_oldSkul][_oldState]->GetCurClip());
	_oldState = _curState;
	_oldSkul = _curSkul;
}