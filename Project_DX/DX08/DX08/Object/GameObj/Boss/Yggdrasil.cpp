#include "framework.h"
#include "Yggdrasil.h"

Yggdrasil::Yggdrasil()
{
	_maxHp = 100;
	_curHp = _maxHp;
	_isAlive = true;

	MakeShared();
	SetParent();
	Adjust();
	SetEffect();
	SetCallBack();
}

Yggdrasil::~Yggdrasil()
{
}

void Yggdrasil::Update()
{
	_reverseBuffer->Update();
	_filterBuffer->Update();
	_colorBuffer->Update();

	if (_isAlive == false)
	{
		AfterDead();
		return;
	}

	_body->Update();

	_headCol->Update();
	_rightBranchCol->Update();
	_leftBranchCol->Update();
	_rightHandCol->Update();
	_leftHandCol->Update();

	_rightHand->Update();
	_leftHand->Update();

	_spikeCol->Update();

	Idle();

	SwitchAttackType();

	Branches();

	if (_curAttackDelay > 0.0f)
		_curAttackDelay -= DELTA_TIME;

	Attacks();

	Spike();

	if (_isDamaged)
	{
		_damagedDelay -= DELTA_TIME;
		if (_damagedDelay < 0)
		{
			_colorBuffer->_data.color.x = 0;
			_damagedDelay = 0.1f;
			_isDamaged = false;
		}
	}
}

void Yggdrasil::Render()
{
	_reverseBuffer->SetPSBuffer(0);
	_filterBuffer->SetPSBuffer(1);
	_colorBuffer->SetPSBuffer(2);

	if (_isAlive == false)
	{
		if (_deadDelay < 0)
			return;

		_body->Render();

		return;
	}
	_body->Render();

	_headCol->Render();
	_rightBranchCol->Render();
	_leftBranchCol->Render();
}

void Yggdrasil::HandRender()
{
	if (_isAlive == false)
	{
		if (_deadDelay < 0)
			return;

		_rightHand->Render();
		_leftHand->Render();

		return;
	}

	_rightHand->Render();
	_leftHand->Render();

	_rightHandCol->Render();
	_leftHandCol->Render();
	
	_spikeCol->Render();
}

void Yggdrasil::Damaged(int damage)
{
	_curHp -= damage;
	_isDamaged = true;

	_colorBuffer->_data.color.x = 0.4f;

	if (_curHp < 0)
	{
		_curHp = 0;
		Dead();
	}
}

void Yggdrasil::Dead()
{
	if (_isAlive == false)
		return;

	FADEPANEL->SetColor({ 1.0f, 1.0f, 1.0f });
	FADEPANEL->SetDelay(3.0f);
	FADEPANEL->StartFadeIn();
	_filterBuffer->_data.selected = 1;
	_filterBuffer->_data.value1 = 1000.0f;
	DeActivate();
	EFFECT->Stop("Sweeping_4x1");

	INVENTORY->AddMoney(500);

	SOUND->Play("State_Earthquake");
	SOUND->StopBgm();
}

void Yggdrasil::SetOriginPos(Vector2 pos)
{
	_originBodyPos = pos;
	_body->GetTransform()->SetPos(pos);

	_rightHand->GetTransform()->SetPos(pos);
	_rightHand->GetTransform()->MoveX(-350);
	_rightHand->GetTransform()->MoveY(-120);
	_originRightHandPos = _rightHand->GetTransform()->GetWorldPos();

	_leftHand->GetTransform()->SetPos(pos);
	_leftHand->GetTransform()->MoveX(350);
	_leftHand->GetTransform()->MoveY(-120);
	_originLeftHandPos = _leftHand->GetTransform()->GetWorldPos();
}

void Yggdrasil::Activate()
{
	_isAlive = true;
	_curState = State::IDLE;
	_curAttackDelay = _maxAttackDelay;
	_body->GetTransform()->SetAngle(0);
	_rightBranchCol->Activate();
	_leftBranchCol->Activate();
	_headCol->Activate();
	_curHp = _maxHp;
	_deadDelay = 3.0f;
	_filterBuffer->_data.selected = 0;
	_colorBuffer->_data.color = { 0, 0, 0, 0 };
}

void Yggdrasil::MakeShared()
{
	_body = make_shared<Quad>(L"Resources/Texture/Boss/Yggdrasil/Body.png");

	_rightHand = make_shared<Quad>(L"Resources/Texture/Boss/Yggdrasil/rightHand.png");
	
	_leftHand = make_shared<Quad>(L"Resources/Texture/Boss/Yggdrasil/leftHand.png");

	_filterBuffer = make_shared<FilterBuffer>();
	_colorBuffer = make_shared<ColorBuffer>();
	_reverseBuffer = make_shared<ReverseBuffer>();

	_headCol = make_shared<CircleCollider>(125);
	_rightBranchCol = make_shared<RectCollider>(Vector2(130, 10));
	_leftBranchCol = make_shared<RectCollider>(Vector2(125, 10));
	_rightHandCol = make_shared<RectCollider>(Vector2(200, 210));
	_leftHandCol = make_shared<RectCollider>(Vector2(200, 210));

	_spikeCol = make_shared<RectCollider>(Vector2(30, 250));
}

void Yggdrasil::SetParent()
{
	_headCol->GetTransform()->SetParent(_body->GetTransform());
	_rightBranchCol->GetTransform()->SetParent(_body->GetTransform());
	_leftBranchCol->GetTransform()->SetParent(_body->GetTransform());
	_rightHandCol->GetTransform()->SetParent(_rightHand->GetTransform());
	_leftHandCol->GetTransform()->SetParent(_leftHand->GetTransform());
}

void Yggdrasil::Adjust()
{
	_headCol->GetTransform()->MoveX(20);
	_headCol->GetTransform()->MoveY(20);

	_rightBranchCol->GetTransform()->MoveX(-120);
	_rightBranchCol->GetTransform()->MoveY(-130);

	_leftBranchCol->GetTransform()->MoveX(177);
	_leftBranchCol->GetTransform()->MoveY(-72);

	_rightHandCol->GetTransform()->MoveX(20);
	_rightHandCol->GetTransform()->MoveY(-35);
	_rightHandCol->DeActivate();

	_leftHandCol->GetTransform()->MoveX(-20);
	_leftHandCol->GetTransform()->MoveY(-35);
	_leftHandCol->DeActivate();

	_body->SetPS(ADD_PS(L"Shader/ColorFilterPixelShader.hlsl"));
	_leftHand->SetPS(ADD_PS(L"Shader/ColorFilterPixelShader.hlsl"));
	_rightHand->SetPS(ADD_PS(L"Shader/ColorFilterPixelShader.hlsl"));
	_filterBuffer->_data.selected = 0;
	_reverseBuffer->_data.reverse = false;
}

void Yggdrasil::SetEffect()
{
	wstring file = L"Resources/Texture/Effect/Spike_15x1.png";
	EFFECT->AddEffect(file, Vector2(15, 1), Vector2(1500, 271), 0.05f);

	file = L"Resources/Texture/Effect/WarnSign_10x1.png";
	EFFECT->AddEffect(file, Vector2(10, 1), Vector2(1680, 73), 0.03f);

	file = L"Resources/Texture/Effect/FistSlamImpact_7x4.png";
	EFFECT->AddEffect(file, Vector2(7, 4), Vector2(5754, 2048));

	file = L"Resources/Texture/Effect/Sweeping_4x1.png";
	EFFECT->AddEffect(file, Vector2(4, 1), Vector2(1872, 176), 0.05f, Action::LOOP, 1U);
}

void Yggdrasil::SetCallBack()
{
	EFFECT->SetMidCallBack("Spike_15x1", std::bind(&Yggdrasil::SpikeFlipDir, this), 6);
	EFFECT->SetCallBack("Spike_15x1", std::bind(&Yggdrasil::SpikeStop, this));
	EFFECT->SetCallBack("WarnSign_10x1", std::bind(&Yggdrasil::SpikeAttack, this));
}

void Yggdrasil::Hit()
{
	int damage = rand() % (_maxDamage - _minDamage) + _minDamage;
	HIT_RESULT result;

	if (_spikeActive)
	{
		result = _spikeCol->SideCollision(PLAYER->GetBodyCollider());
		if (result.isHit)
			PLAYER->Damaged(damage, result.dir);
	}
	else if (_isRightHand)
	{
		result = _rightHandCol->SideCollision(PLAYER->GetBodyCollider());
		if (result.isHit)
			PLAYER->Damaged(damage, result.dir);
	}
	else
	{
		result = _leftHandCol->SideCollision(PLAYER->GetBodyCollider());
		if (result.isHit)
			PLAYER->Damaged(damage, result.dir);
	}
}

void Yggdrasil::StampAttackReady()
{
	_rightHand->GetTransform()->Move(SetLERP(_rightHand->GetTransform()->GetWorldPos(), Vector2(_originRightHandPos.x, _originRightHandPos.y + 300), DELTA_TIME * 2.0f));
	_leftHand->GetTransform()->Move(SetLERP(_leftHand->GetTransform()->GetWorldPos(), Vector2(_originLeftHandPos.x, _originLeftHandPos.y + 300), DELTA_TIME * 2.0f));
}

void Yggdrasil::StampAttack()
{
	Hit();

	if (_isRightHand)
	{
		_rightHand->GetTransform()->Move(SetLERP(_rightHand->GetTransform()->GetWorldPos(), _attackPos, DELTA_TIME * 8.0f));
	}
	else
	{
		_leftHand->GetTransform()->Move(SetLERP(_leftHand->GetTransform()->GetWorldPos(), _attackPos, DELTA_TIME * 8.0f));
	}

}

void Yggdrasil::StampAttackAfter()
{
	if (_isRightHand)
	{
		_rightHand->GetTransform()->Move(SetLERP(_rightHand->GetTransform()->GetWorldPos(), _attackPos, DELTA_TIME * 8.0f));

		HIT_RESULT result = _rightHandCol->Block(PLAYER->GetFootCollider());
		if (result.dir == Direction::UP)
			PLAYER->Ground();
	}
	else
	{
		_leftHand->GetTransform()->Move(SetLERP(_leftHand->GetTransform()->GetWorldPos(), _attackPos, DELTA_TIME * 8.0f));

		HIT_RESULT result = _leftHandCol->Block(PLAYER->GetFootCollider());
		if (result.dir == Direction::UP)
			PLAYER->Ground();
	}
}

void Yggdrasil::SpikeAttack()
{
	_spikeActive = true;
	_spikeUp = true;
	_spikeCol->GetTransform()->SetPos(Vector2(_spikePos.x, _spikePos.y - 300.0f));
	EFFECT->Stop("WarnSign_10x1");
	EFFECT->Play("Spike_15x1", _spikePos);

	SOUND->Play("Hit_Sword_Small");
}

void Yggdrasil::SpikeFlipDir()
{
	_spikeUp = false;
}

void Yggdrasil::SpikeStop()
{
	_spikeActive = false;
	EFFECT->Stop("Spike_15x1");
}

void Yggdrasil::Spike()
{
	if (_spikeReady)
	{
		_curSpikeDelay -= DELTA_TIME;

		if (_curSpikeDelay < 0.0f)
		{
			_spikePos.x = PLAYER->GetFootCollider()->GetTransform()->GetWorldPos().x;
			EFFECT->Play("WarnSign_10x1", { _spikePos.x, _spikePos.y - 130 });
			_curSpikeDelay = _maxSpikeDelay;
			_spikeReady = false;
		}
	}
	if (_spikeActive)
	{
		if (_spikeUp)
		{
			if (_spikeCol->GetTransform()->GetWorldPos().y < _spikePos.y)
				_spikeCol->GetTransform()->MoveY(1000.0f * DELTA_TIME);
		}
		else
		{
			if (_spikeCol->GetTransform()->GetWorldPos().y > _spikePos.y - 300)
				_spikeCol->GetTransform()->MoveY(-1000.0f * DELTA_TIME);
		}

		Hit();
	}
}

void Yggdrasil::SweepAttackReady()
{
	if (_isRightHand)
	{
		if (_body->GetTransform()->GetAngle() < 0.25f)
			_body->GetTransform()->AddAngle(SetLERP(0, 0.3f, DELTA_TIME * 1.5f));
		else if (_body->GetTransform()->GetAngle() > 0.25f)
			_body->GetTransform()->SetAngle(0.25f);
		_body->GetTransform()->Move(SetLERP(_body->GetTransform()->GetWorldPos(), Vector2(_originBodyPos.x - 250, _originBodyPos.y - 100), DELTA_TIME * 2.0f));
		_rightHand->GetTransform()->Move(SetLERP(_rightHand->GetTransform()->GetWorldPos(), Vector2(_originRightHandPos.x - 1500, _attackPos.y), DELTA_TIME * 2.0f));
		_leftHand->GetTransform()->Move(SetLERP(_leftHand->GetTransform()->GetWorldPos(), Vector2(_originLeftHandPos.x - 250, _originLeftHandPos.y - 100), DELTA_TIME * 2.0f));
	}
	else
	{
		if (_body->GetTransform()->GetAngle() > -0.25f)
			_body->GetTransform()->AddAngle(SetLERP(0, -0.3f, DELTA_TIME * 1.5f));
		else if (_body->GetTransform()->GetAngle() < -0.25f)
			_body->GetTransform()->SetAngle(-0.25f);
		_body->GetTransform()->Move(SetLERP(_body->GetTransform()->GetWorldPos(), Vector2(_originBodyPos.x + 250, _originBodyPos.y - 100), DELTA_TIME * 2.0f));
		_rightHand->GetTransform()->Move(SetLERP(_rightHand->GetTransform()->GetWorldPos(), Vector2(_originRightHandPos.x + 250, _originRightHandPos.y - 100), DELTA_TIME * 2.0f));
		_leftHand->GetTransform()->Move(SetLERP(_leftHand->GetTransform()->GetWorldPos(), Vector2(_originLeftHandPos.x + 1500, _attackPos.y), DELTA_TIME * 2.0f));
	}
	_rightBranchCol->DeActivate();
	_leftBranchCol->DeActivate();
}

void Yggdrasil::SweepAttack()
{
	Hit();

	if (_isRightHand)
	{
		if (_body->GetTransform()->GetAngle() > -0.35f)
			_body->GetTransform()->AddAngle(SetLERP(0, -0.6f, DELTA_TIME));
		else if (_body->GetTransform()->GetAngle() < -0.35f)
			_body->GetTransform()->SetAngle(-0.35f);
		_body->GetTransform()->Move(SetLERP(_body->GetTransform()->GetWorldPos(), Vector2(_originBodyPos.x + 250, _originBodyPos.y - 100), DELTA_TIME * 2.0f));
		_rightHand->GetTransform()->Move(SetLERP(_rightHand->GetTransform()->GetPos(), Vector2(_originRightHandPos.x + 2500, _attackPos.y), DELTA_TIME));
		_leftHand->GetTransform()->Move(SetLERP(_leftHand->GetTransform()->GetPos(), Vector2(_originLeftHandPos.x + 250, _attackPos.y), DELTA_TIME * 2.0f));
	}
	else
	{
		if (_body->GetTransform()->GetAngle() < 0.35f)
			_body->GetTransform()->AddAngle(SetLERP(0, 0.6f, DELTA_TIME));
		else if (_body->GetTransform()->GetAngle() > 0.35f)
			_body->GetTransform()->SetAngle(0.35f);
		_body->GetTransform()->Move(SetLERP(_body->GetTransform()->GetWorldPos(), Vector2(_originBodyPos.x - 250, _originBodyPos.y - 100), DELTA_TIME * 2.0f));
		_rightHand->GetTransform()->Move(SetLERP(_rightHand->GetTransform()->GetPos(), Vector2(_originRightHandPos.x - 250, _attackPos.y), DELTA_TIME * 2.0f));
		_leftHand->GetTransform()->Move(SetLERP(_leftHand->GetTransform()->GetPos(), Vector2(_originLeftHandPos.x - 2500, _attackPos.y), DELTA_TIME));
	}
}

void Yggdrasil::SweepAttackAfter()
{
	if (_isRightHand)
	{
		if (_body->GetTransform()->GetAngle() > -0.35f)
			_body->GetTransform()->AddAngle(SetLERP(0, -0.6f, DELTA_TIME));
		else if (_body->GetTransform()->GetAngle() < -0.35f)
			_body->GetTransform()->SetAngle(-0.35f);
		_body->GetTransform()->Move(SetLERP(_body->GetTransform()->GetWorldPos(), Vector2(_originBodyPos.x + 250, _originBodyPos.y - 100), DELTA_TIME * 2.0f));
		_rightHand->GetTransform()->Move(SetLERP(_rightHand->GetTransform()->GetPos(), Vector2(_originRightHandPos.x + 2500, _attackPos.y), DELTA_TIME));
		_leftHand->GetTransform()->Move(SetLERP(_leftHand->GetTransform()->GetPos(), Vector2(_originLeftHandPos.x + 250, _attackPos.y), DELTA_TIME * 2.0f));
	}
	else
	{
		if (_body->GetTransform()->GetAngle() < 0.35f)
			_body->GetTransform()->AddAngle(SetLERP(0, 0.6f, DELTA_TIME));
		else if (_body->GetTransform()->GetAngle() > 0.35f)
			_body->GetTransform()->SetAngle(0.35f);
		_body->GetTransform()->Move(SetLERP(_body->GetTransform()->GetWorldPos(), Vector2(_originBodyPos.x - 250, _originBodyPos.y - 100), DELTA_TIME * 2.0f));
		_rightHand->GetTransform()->Move(SetLERP(_rightHand->GetTransform()->GetPos(), Vector2(_originRightHandPos.x - 250, _attackPos.y), DELTA_TIME * 2.0f));
		_leftHand->GetTransform()->Move(SetLERP(_leftHand->GetTransform()->GetPos(), Vector2(_originLeftHandPos.x - 2200, _attackPos.y), DELTA_TIME));
	}
}

void Yggdrasil::SweepAttackEnd()
{
	if (_isRightHand)
	{
		if (_body->GetTransform()->GetAngle() < 0)
			_body->GetTransform()->AddAngle(SetLERP(0, 0.3f, DELTA_TIME));
		else if (_body->GetTransform()->GetAngle() > 0)
			_body->GetTransform()->SetAngle(0);
		_body->GetTransform()->Move(SetLERP(_body->GetTransform()->GetWorldPos(), _originBodyPos, DELTA_TIME * 2.0f));
		_rightHand->GetTransform()->Move(SetLERP(_rightHand->GetTransform()->GetPos(), _originRightHandPos, DELTA_TIME));
		_leftHand->GetTransform()->Move(SetLERP(_leftHand->GetTransform()->GetPos(), _originLeftHandPos, DELTA_TIME * 2.0f));
	}
	else
	{
		if (_body->GetTransform()->GetAngle() > 0)
			_body->GetTransform()->AddAngle(SetLERP(0, -0.3f, DELTA_TIME));
		else if (_body->GetTransform()->GetAngle() < 0)
			_body->GetTransform()->SetAngle(0);
		_body->GetTransform()->Move(SetLERP(_body->GetTransform()->GetWorldPos(), _originBodyPos, DELTA_TIME * 2.0f));
		_rightHand->GetTransform()->Move(SetLERP(_rightHand->GetTransform()->GetPos(), _originRightHandPos, DELTA_TIME * 2.0f));
		_leftHand->GetTransform()->Move(SetLERP(_leftHand->GetTransform()->GetPos(), _originLeftHandPos, DELTA_TIME));
	}
}

void Yggdrasil::Branches()
{
	if (PLAYER->GetJumpPower() <= 0.0f)
	{
		HIT_RESULT result;
		if (_rightBranchCol->GetActive())
		{
			if (PLAYER->GetIsBungee() == false)
			{
				result = _rightBranchCol->TopBlock(PLAYER->GetFootCollider());
				if (result.dir == Direction::UP)
					PLAYER->Ground();
			}
		}
		if (_leftBranchCol->GetActive())
		{
			if (PLAYER->GetIsBungee() == false)
			{
				result = _leftBranchCol->TopBlock(PLAYER->GetFootCollider());
				if (result.dir == Direction::UP)
					PLAYER->Ground();
			}
		}
	}
}

void Yggdrasil::Attacks()
{
	if (_curState == State::ATTACK)
	{
		switch (_attackType)
		{
		case Yggdrasil::STAMP:
			if ((_isRightHand && _rightHandCol->GetTransform()->GetWorldPos().y <= _attackPos.y + 10.0f) || (!_isRightHand && _leftHandCol->GetTransform()->GetWorldPos().y <= _attackPos.y + 10.0f))
			{
				CAMERA->ShakeStart(10, 1);
				_curState = State::ATTACKAFTER;
				_curAttackDelay = _maxAttackDelay;

				_spikeReady = true;
				EFFECT->Play("FistSlamImpact_7x4", Vector2(_attackPos.x, _attackPos.y + 130));

				SOUND->Play("ElderEnt_FistSlam");
				SOUND->Play("Atk_Smoke_Long");
			}
			break;
		case Yggdrasil::SWEEP:
			if (_isRightHand)
			{
				if (_rightHand->GetTransform()->GetWorldPos().x > _originRightHandPos.x + 1700)
				{
					_curState = State::ATTACKAFTER;
					_curAttackDelay = _maxAttackDelay;
				}
			}
			else
			{
				if (_leftHand->GetTransform()->GetWorldPos().x < _originLeftHandPos.x - 1700)
				{
					_curState = State::ATTACKAFTER;
					_curAttackDelay = _maxAttackDelay;
				}
			}

			if (SOUND->IsPlaySound("ElderEnt_Sweeping") == false)
				SOUND->Play("ElderEnt_Sweeping");
			break;
		default:
			break;
		}
	}
	else if (_curAttackDelay <= 0.0f)
	{
		float curX;
		int attackType;
		switch (_curState)
		{
		case State::IDLE:
			attackType = rand() % 2;
			switch (attackType)
			{
			case 0:
				_attackType = AttackType::STAMP;
				break;
			case 1:
				_attackType = AttackType::SWEEP;
				break;
			default:
				break;
			}
			_curState = State::ATTACKREADY;
			_curAttackDelay = _maxAttackDelay;
			curX = PLAYER->GetFootCollider()->GetTransform()->GetPos().x;
			if (curX > _body->GetTransform()->GetWorldPos().x)
				_isRightHand = false;
			else
				_isRightHand = true;

			SOUND->Play("ElderEnt_Up_1");
			break;
		case State::ATTACKREADY:
			if (_attackType == AttackType::SWEEP)
			{
				if (_isRightHand)
				{
					EFFECT->SetParent("Sweeping_4x1", _rightHand->GetTransform());
					EFFECT->Play("Sweeping_4x1", Vector2(-210, -50), true);
				}
				else
				{
					EFFECT->SetParent("Sweeping_4x1", _leftHand->GetTransform());
					EFFECT->Play("Sweeping_4x1", Vector2(210, -50), false);
				}
				CAMERA->ShakeStart(5, 2);
			}
			_curState = State::ATTACK;
			_attackPos.x = PLAYER->GetFootCollider()->GetTransform()->GetPos().x;
			if (_isRightHand)
			{
				_rightHandCol->GetTransform()->Update();
				_rightHandCol->Activate();
			}
			else
			{
				_leftHandCol->GetTransform()->Update();
				_leftHandCol->Activate();
			}
			break;
		case State::ATTACKAFTER:
			if (_attackType = AttackType::SWEEP)
			{
				EFFECT->Stop("Sweeping_4x1");
			}
			_curState = State::ATTACKEND;
			if (_isRightHand)
				_rightHandCol->DeActivate();
			else
				_leftHandCol->DeActivate();
			_curAttackDelay = _maxAttackDelay;

			SOUND->Play("ElderEnt_Groggy_Recovery", false, 0.1f);
			break;
		case State::ATTACKEND:
			_curState = State::IDLE;
			_curAttackDelay = _maxAttackDelay;
			break;
		default:
			break;
		}
	}
}

void Yggdrasil::SetIdle()
{
	_body->GetTransform()->Move(SetLERP(_body->GetTransform()->GetWorldPos(), _originBodyPos, DELTA_TIME * 8.0f));
	_rightHand->GetTransform()->Move(SetLERP(_rightHand->GetTransform()->GetWorldPos(), _originRightHandPos, DELTA_TIME * 8.0f));
	_leftHand->GetTransform()->Move(SetLERP(_leftHand->GetTransform()->GetWorldPos(), _originLeftHandPos, DELTA_TIME * 8.0f));
	_rightBranchCol->Activate();
	_leftBranchCol->Activate();
}

Vector2 Yggdrasil::SetLERP(Vector2 objPos, Vector2 targetPos, float speed)
{
	Vector2 curPos = objPos;
	Vector2 goalPos = targetPos - objPos;
	Vector2 distance = LERP(Vector2(0, 0), goalPos, speed);

	return distance;
}

float Yggdrasil::SetLERP(float start, float end, float speed)
{
	float curPos = start;
	float goalPos = end - start;
	float distance = LERP(0, goalPos, speed);

	return distance;
}

void Yggdrasil::Idle()
{
	float curY = _body->GetTransform()->GetPos().y;
	float goalY;
	float speed;

	if (_up)
	{
		speed = 10.0f;
		goalY = _originBodyPos.y + 5.0f;
		if (curY >= goalY - 0.15f)
		{
			_up = false;
		}
	}
	else
	{
		speed = -10.0f;
		goalY = _originBodyPos.y - 5.0f;
		if (curY <= goalY + 0.15f)
		{
			_up = true;
		}
	}

	_body->GetTransform()->MoveY(speed * DELTA_TIME);
	_rightHand->GetTransform()->MoveY(speed * DELTA_TIME);
	_leftHand->GetTransform()->MoveY(speed * DELTA_TIME);
}

void Yggdrasil::SwitchAttackType()
{
	switch (_attackType)
	{
	case Yggdrasil::STAMP:
		switch (_curState)
		{
		case State::IDLE:
			SetIdle();
			break;
		case State::ATTACKREADY:
			StampAttackReady();
			break;
		case State::ATTACK:
			StampAttack();
			break;
		case State::ATTACKAFTER:
			StampAttackAfter();
			break;
		case State::ATTACKEND:
			StampAttackReady();
			break;
		default:
			break;
		}
		break;
	case Yggdrasil::SWEEP:
		switch (_curState)
		{
		case State::IDLE:
			SetIdle();
			break;
		case State::ATTACKREADY:
			SweepAttackReady();
			break;
		case State::ATTACK:
			SweepAttack();
			break;
		case State::ATTACKAFTER:
			SweepAttackAfter();
			break;
		case State::ATTACKEND:
			SweepAttackEnd();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Yggdrasil::DeActivate()
{
	_rightBranchCol->DeActivate();
	_leftBranchCol->DeActivate();
	_headCol->DeActivate();
	_isAlive = false;
}

void Yggdrasil::AfterDead()
{
	if (_deadDelay < 0)
		return;

	_deadDelay -= DELTA_TIME;
	float tempValue = _deadDelay / 3.0f;
	_filterBuffer->_data.value1 = LERP(_filterBuffer->_data.value1, 0, 0.02f);
	_colorBuffer->_data.color = { 1 - tempValue, 0.0f, 1 - tempValue, 0.0f };

	CAMERA->ShakeStart((1 - tempValue) * 20, DELTA_TIME);
}