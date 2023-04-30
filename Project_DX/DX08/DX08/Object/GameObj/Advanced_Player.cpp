#include "framework.h"
#include "Advanced_Player.h"

Advanced_Player::Advanced_Player()
{
	_maxHp = _baseMaxHp;
	_curHp = _maxHp;
	_maxDamage = 30;
	_minDamage = 20;

	_attackCol = make_shared<CircleCollider>(50);
	_attackCol->GetTransform()->SetParent(_footCol->GetTransform());
	_attackCol->GetTransform()->MoveX(5);
	_attackCol->GetTransform()->MoveY(25);
	_attackCol->DeActivate();

	_reverseBuffer = make_shared<ReverseBuffer>();

	_skillCol = make_shared<CircleCollider>(50);
	_skillCol->GetTransform()->SetParent(_attackCol->GetTransform());
	_skillCol->DeActivate();

	_fireArrow = make_shared<FireArrow>();
	_meteor = make_shared<Meteor>();
	_throwHead = make_shared<ThrowHead>();

	SetCallback();
}

Advanced_Player::~Advanced_Player()
{
}

void Advanced_Player::Update()
{
	_reverseBuffer->Update();
	_attackCol->Update();
	_skillCol->Update();

	_throwHead->Update();
	_fireArrow->Update();
	_meteor->Update();

	SetIdle();
	Attack();
	Flip();
	Jump();
	Dash();
	Move();
	Fall();
	Skill();
	Skill2();
	Bungee();
	if (KEY_DOWN(VK_SPACE))
		SwapSkul();

	Player::Update();

	float ratio = static_cast<float>(_curHp) / static_cast<float>(_maxHp);
	UI->SetHpRatio(ratio);

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
			if (_curSkul == SkulType::HEADLESS)
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

	if (_isSkillUsed)
	{
		_curSkillCD -= DELTA_TIME;
		UI->SetSkillRatio(0, _curSkillCD / _maxSkillCD);

		if (_curSkillCD < 0.0f)
		{
			_isSkillUsed = false;
			_curSkillCD = _maxSkillCD;
		}
	}

	if (_isSkill2Used)
	{
		_curSkill2CD -= DELTA_TIME;
		UI->SetSkillRatio(1, _curSkill2CD / _maxSkillCD);

		if (_curSkill2CD < 0.0f)
		{
			_isSkill2Used = false;
			_curSkill2CD = _maxSkillCD;
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

	_meteor->Render();
	_fireArrow->Render();
	_throwHead->Render();

	_attackCol->Render();
	_skillCol->Render();
}

void Advanced_Player::PostRender()
{
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
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK || _curState == State::DASH || _curState == State::SKILL || _curState == State::SKILL2)
			return;
		if (_direction == Direction::RIGHT)
			return;
		_direction = Direction::RIGHT;
		_sprites[_curSkul][_curState]->SetDirection(_direction);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK || _curState == State::DASH || _curState == State::SKILL || _curState == State::SKILL2)
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
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::DASH || _curState == State::SKILL || _curState == State::SKILL2)
			return;
		_footCol->GetTransform()->MoveX(_speed * DELTA_TIME);
		if (_curState == State::JUMP || _curState == State::JUMPATTACK || _curState == State::FALLREPEAT || _curState == State::FALL)
			return;
		_isGround = false;
		SetAction(State::WALK);
	}
	if (KEY_PRESS(VK_LEFT))
	{
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::DASH || _curState == State::SKILL || _curState == State::SKILL2)
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
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK || _curState == State::SKILL || _curState == State::DASH || _curState == State::SKILL2)
			return;
		if (_isDoubleJump)
			return;

		if (_isJump)
		{
			_isDoubleJump = true;
			SetAction(State::JUMP);
			_curJumpPower = _maxJumpPower;

			SOUND->Play("Dash_Small"); 
			return;
		}
		_isGround = false;
		_isJump = true;
		SetAction(State::JUMP);
		_curJumpPower = _maxJumpPower;

		SOUND->Play("Dash_Small");
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

		SOUND->Play("Default_Dash", false, 0.01f);
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
	
	if (_curJumpPower <= 0 && _curState != State::FALLREPEAT && _curState != State::JUMPATTACK && _curState != State::SKILL && _curState != State::SKILL2)
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

	SOUND->Play("Trap_Jump");
}

void Advanced_Player::Attack()
{
	if (KEY_DOWN('X'))
	{
		if (_curState == State::ATTACKA || _curState == State::ATTACKB || _curState == State::JUMPATTACK || _curState == State::DASH || _curState == State::SKILL || _curState == State::SKILL2)
			return;

		if (_curState == State::JUMP || _curState == State::FALLREPEAT || _curState == State::FALL)
		{
			SetAction(State::JUMPATTACK);

			SOUND->Play("Skul_Jump_Atk");
		}
		else if (_isAttackB)
		{
			_isAttackB = false;
			_curComboDuration = _maxComboDuration;
			SetAction(State::ATTACKB);

			SOUND->Play("Skul_Atk_2");
		}
		else
		{
			_isAttackB = true;
			SetAction(State::ATTACKA);

			SOUND->Play("Skul_Atk_1");
		}
	}
}

void Advanced_Player::AttackHit()
{
	_attackCol->DeActivate();

	if (_curSkul == SkulType::SKUL || _curSkul == SkulType::HEADLESS || _curSkul == SkulType::WIZARDN || _curSkul == SkulType::WIZARDR || _curSkul == SkulType::WIZARDU || _curSkul == SkulType::WIZARDL)
	{
		if (_isAttackB)
			SOUND->Play("Wizard_Hit");
		else
			SOUND->Play("Wizard_Hit_Large");
	}
	else
	{
		SOUND->Play("Hit_Sword_Small");
	}
}

void Advanced_Player::Skill()
{
	if (KEY_DOWN('A'))
	{
		if (_curSkul == SkulType::HEADLESS)
			return;
		if (_isSkillUsed)
			return;

		_isSkillUsed = true;
		SetAction(State::SKILL);

		if (_curSkul == SkulType::SKUL)
		{
			_skillType = SkillType::THROWHEAD;

			SOUND->Play("Skul_SkullThrowing");
		}
		else if (_curSkul == SkulType::WAREWOLFN || _curSkul == SkulType::WAREWOLFR || _curSkul == SkulType::WAREWOLFU || _curSkul == SkulType::WAREWOLFL)
		{
			_skillType = SkillType::MELEE;

			SOUND->Play("Skul_Atk_2");
		}
		else if (_curSkul == SkulType::WIZARDN || _curSkul == SkulType::WIZARDR || _curSkul == SkulType::WIZARDU || _curSkul == SkulType::WIZARDL)
		{
			_skillType = SkillType::FIREARROW;

			SOUND->Play("Wizard_FireArrow_Ready");
		}
	}
}

void Advanced_Player::Skill2()
{
	if (KEY_DOWN('S'))
	{
		if (_curSkul == SkulType::HEADLESS || _curSkul == SkulType::SKUL)
			return;
		if (_isSkill2Used)
			return;

		_isSkill2Used = true;
		SetAction(State::SKILL2);

		if (_curSkul == SkulType::WAREWOLFN || _curSkul == SkulType::WAREWOLFR || _curSkul == SkulType::WAREWOLFU || _curSkul == SkulType::WAREWOLFL)
		{
			_skillType == SkillType::MELEE;

			SOUND->Play("Skul_Atk_2");
		}
		else if (_curSkul == SkulType::WIZARDN || _curSkul == SkulType::WIZARDR || _curSkul == SkulType::WIZARDU || _curSkul == SkulType::WIZARDL)
		{
			_skillType = SkillType::METEOR;

			SOUND->Play("Wizard_Meteor_Throw");
		}
	}
}

void Advanced_Player::ThrowHeadHit()
{
	_headDelay = _maxHeadDelay;
	_isHeadOn = true;
	if (_curSkul == SkulType::HEADLESS)
		SetSkul(SkulType::SKUL);
	_throwHead->DeActivate();
	_footCol->GetTransform()->SetPos(_throwHead->GetCollider()->GetTransform()->GetWorldPos());

	SOUND->Play("Skul_SkullBack");
}

void Advanced_Player::FireArrowHit()
{
	_fireArrow->Hit();

	SOUND->Play("Atk_Flame_Very_Small");
}

void Advanced_Player::MeteorHit(int index)
{
	_meteor->Hit(index);

	SOUND->Play("Atk_Flame_Very_Small");
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

	CAMERA->ShakeStart(10.0f, 0.2f);
	FADEPANEL->StartHitted();
	_curHp -= damage;

	SOUND->Play("Wizard_Hit");
}

void Advanced_Player::CastThrowHead()
{
	_throwHead->SetPos(_bodyCol->GetTransform()->GetWorldPos());
	_throwHead->SetActive();
	if (_direction == Direction::RIGHT)
		_throwHead->SetRight(true);
	else if (_direction == Direction::LEFT)
		_throwHead->SetRight(false);
	SetSkul(SkulType::HEADLESS);
}

void Advanced_Player::CastFireArrow()
{
	_fireArrow->SetPos(_bodyCol->GetTransform()->GetWorldPos());
	_fireArrow->SetActive();
	if (_direction == Direction::RIGHT)
		_fireArrow->SetRight(true);
	else if (_direction == Direction::LEFT)
		_fireArrow->SetRight(false);
	SetAction(State::IDLE);

	SOUND->Play("Wizard_FireArrow_Shot");
}

void Advanced_Player::CastMeteor()
{
	_meteor->SetPos(_bodyCol->GetTransform()->GetWorldPos());
	_meteor->SetRandomSpeeds();
	_meteor->SetActive();
	SetAction(State::IDLE);
}

void Advanced_Player::Heal(int value)
{
	if (value < 0)
		return;

	_curHp += value;
	if (_curHp > _maxHp)
		_curHp = _maxHp;

	SOUND->Play("GetHealingOrb");
}

void Advanced_Player::Dead()
{

}

void Advanced_Player::Revive()
{

}

const float& Advanced_Player::GetAttackDamage()
{
	int ad = (rand() % (_maxDamage - _minDamage) + _minDamage);
	ad += _statAttributes.ad;

	int temp = rand() % 100;
	if (temp < _critPercent + _statAttributes.crp)
		ad *= 2;

	return ad;
}

const float& Advanced_Player::GetSkillDamage()
{
	int power;
	switch (_skillType)
	{
	case SkillType::NONE:
		power = 0;
		break;
	case SkillType::MELEE:
		power = _maxDamage;
		break;
	case SkillType::THROWHEAD:
		power = _throwHead->GetPower();
		break;
	case SkillType::FIREARROW:
		power = _fireArrow->GetPower();
		break;
	case SkillType::METEOR:
		power = _meteor->GetPower();
		break;
	default:
		break;
	}
	power += rand() % 5;
	power += _statAttributes.ap;

	int temp = rand() % 100;
	if (temp < _critPercent + _statAttributes.crp)
		power *= 2;

	return power;
}

void Advanced_Player::SetEquipStats(StatAttributes stats)
{
	_statAttributes = stats;

	_maxHp = _baseMaxHp + _statAttributes.hp;
	_def = _baseDef + _statAttributes.def;
	_critPercent = _baseCrp + _statAttributes.crp;
	_maxHeadDelay = _baseScd * ((float)(100 - _statAttributes.scd) / 100);
	_maxSkillCD = _baseScd * ((float)(100 - _statAttributes.scd) / 100);
	_maxChangeCD = _baseCcd * ((float)(100 - _statAttributes.ccd) / 100);
}

void Advanced_Player::SwapSkul()
{
	vector<ItemInfo> data = INVENTORY->GetEquipedSkulInfo();

	if (data[_isFirstSkul].itemCode == 0)
		return;

	_isFirstSkul = !_isFirstSkul;
	UI->SwapSkul(_isFirstSkul);
	switch (data[!_isFirstSkul].itemCode)
	{
	case 1:
		SetSkul(SkulType::SKUL);
		break;
	case 2:
		SetSkul(SkulType::WAREWOLFN);
		break;
	case 3:
		SetSkul(SkulType::WIZARDN);
		break;
	case 4:
		SetSkul(SkulType::WAREWOLFR);
		break;
	case 5:
		SetSkul(SkulType::WIZARDR);
		break;
	case 6:
		SetSkul(SkulType::WAREWOLFU);
		break;
	case 7:
		SetSkul(SkulType::WIZARDU);
		break;
	case 8:
		SetSkul(SkulType::WAREWOLFL);
		break;
	case 9:
		SetSkul(SkulType::WIZARDL);
		break;
	default:
		break;
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
	if (_curSkul == SkulType::SKUL && _throwHead->GetCollider()->GetActive())
	{
		_isHeadOn = false;
		SetSkul(SkulType::HEADLESS);
	}
	else if (_curSkul == SkulType::HEADLESS)
	{
		_isHeadOn = true;
		SetSkul(SkulType::SKUL);
	}
	else
	{
		_isHeadOn = true;
		SetAction(State::IDLE);
	}
}

void Advanced_Player::ActivateSkillCol()
{
	_skillCol->GetTransform()->Update();
	_skillCol->Activate();
}

void Advanced_Player::DeactivateSkillCol()
{
	_skillCol->DeActivate();
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
	_actions[SkulType::SKUL][State::SKILL]->SetMidCallBack(std::bind(&Advanced_Player::CastThrowHead, this), 2);

	_actions[SkulType::HEADLESS][State::ATTACKA]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this), 2);
	_actions[SkulType::HEADLESS][State::ATTACKA]->SetMidCallBack(std::bind(&Advanced_Player::AttackColEnd, this), 3);
	_actions[SkulType::HEADLESS][State::ATTACKB]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this), 1);
	_actions[SkulType::HEADLESS][State::ATTACKB]->SetMidCallBack(std::bind(&Advanced_Player::AttackColEnd, this), 2);
	_actions[SkulType::HEADLESS][State::JUMPATTACK]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this), 1);
	_actions[SkulType::HEADLESS][State::JUMPATTACK]->SetMidCallBack(std::bind(&Advanced_Player::AttackColEnd, this), 2);

	for (int i = 2; i < SkulType::SkulTypeSize; i += 2)
	{
		_actions[i][State::ATTACKA]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this), 2);
		_actions[i][State::ATTACKA]->SetMidCallBack(std::bind(&Advanced_Player::AttackColEnd, this), 3);
		_actions[i][State::ATTACKB]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this), 1);
		_actions[i][State::ATTACKB]->SetMidCallBack(std::bind(&Advanced_Player::AttackColEnd, this), 2);
		_actions[i][State::JUMPATTACK]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this), 1);
		_actions[i][State::JUMPATTACK]->SetMidCallBack(std::bind(&Advanced_Player::AttackColEnd, this), 2);
		_actions[i][State::SKILL]->SetMidCallBack(std::bind(&Advanced_Player::ActivateSkillCol, this), 2);
		_actions[i][State::SKILL]->SetMidCallBack(std::bind(&Advanced_Player::DeactivateSkillCol, this), 3);
		_actions[i][State::SKILL]->SetCallBack(std::bind(&Advanced_Player::SkillEnd, this));
		_actions[i][State::SKILL2]->SetCallBack(std::bind(&Advanced_Player::SkillEnd, this));
	}

	for (int i = 3; i < SkulType::SkulTypeSize; i += 2)
	{
		_actions[i][State::ATTACKA]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this), 2);
		_actions[i][State::ATTACKA]->SetMidCallBack(std::bind(&Advanced_Player::AttackColEnd, this), 3);
		_actions[i][State::ATTACKB]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this), 1);
		_actions[i][State::ATTACKB]->SetMidCallBack(std::bind(&Advanced_Player::AttackColEnd, this), 2);
		_actions[i][State::JUMPATTACK]->SetMidCallBack(std::bind(&Advanced_Player::AttackMid, this), 1);
		_actions[i][State::JUMPATTACK]->SetMidCallBack(std::bind(&Advanced_Player::AttackColEnd, this), 2);
		_actions[i][State::SKILL]->SetCallBack(std::bind(&Advanced_Player::CastFireArrow, this));
		_actions[i][State::SKILL2]->SetMidCallBack(std::bind(&Advanced_Player::CastMeteor, this), 2);
	}

	_throwHead->SetEndEvent(std::bind(&Advanced_Player::SkillEnd, this));
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