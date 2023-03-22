#include "framework.h"
#include "Yggdrasil.h"

Yggdrasil::Yggdrasil()
{
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
	if (_isAlive == false)
	{
		return;
	}

	_headCol->Update();
	_rightBranchCol->Update();
	_leftBranchCol->Update();
	_rightHandCol->Update();
	_leftHandCol->Update();

	_body->Update();

	_rightHand->Update();
	_leftHand->Update();

	_spikeCol->Update();

	Idle();

	if (_player.expired() == false)
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

		if (_player.lock()->GetJumpPower() <= 0.0f)
		{
			HIT_RESULT result;
			if (_rightBranchCol->GetActive())
			{
				if (_player.lock()->GetIsBungee() == false)
				{
					result = _rightBranchCol->TopBlock(_player.lock()->GetFootCollider());
					if (result.dir == Direction::UP)
						_player.lock()->Ground();
				}
			}
			if (_leftBranchCol->GetActive())
			{
				if (_player.lock()->GetIsBungee() == false)
				{
					result = _leftBranchCol->TopBlock(_player.lock()->GetFootCollider());
					if (result.dir == Direction::UP)
						_player.lock()->Ground();
				}
			}
		}

		if (_curAttackDelay > 0.0f)
			_curAttackDelay -= DELTA_TIME;
			
		if (_curState == State::ATTACK)
		{
			switch (_attackType)
			{
			case Yggdrasil::STAMP:
				if ((_isRightHand && _rightHandCol->GetTransform()->GetWorldPos().y <= _attackPos.y + 10.0f) || (!_isRightHand && _leftHandCol->GetTransform()->GetWorldPos().y <= _attackPos.y + 10.0f))
				{
					_curState = State::ATTACKAFTER;
					_curAttackDelay = _maxAttackDelay;

					_spikeReady = true;
					EFFECT->Play("FistSlamImpact_7x4", Vector2(_attackPos.x, _attackPos.y + 130));
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
				curX = _player.lock()->GetFootCollider()->GetTransform()->GetPos().x;
				if (curX > _body->GetTransform()->GetWorldPos().x)
					_isRightHand = false; 
				else
					_isRightHand = true;
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

				}
				_curState = State::ATTACK;
				_attackPos.x = _player.lock()->GetFootCollider()->GetTransform()->GetPos().x;
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
				break;
			case State::ATTACKEND:
				_curState = State::IDLE;
				_curAttackDelay = _maxAttackDelay;
				break;
			default:
				break;
			}
		}

		if (_spikeReady)
		{
			_curSpikeDelay -= DELTA_TIME;

			if (_curSpikeDelay < 0.0f)
			{
				_spikePos.x = _player.lock()->GetFootCollider()->GetTransform()->GetWorldPos().x;
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
}

void Yggdrasil::Render()
{
	if (_isAlive == false)
	{
		return;
	}

	_body->Render();

}

void Yggdrasil::PostRender()
{
	if (_isAlive == false)
	{
		return;
	}

	_rightHand->Render();
	_leftHand->Render();

	_headCol->Render();
	_rightBranchCol->Render();
	_leftBranchCol->Render();
	_rightHandCol->Render();
	_leftHandCol->Render();
	
	_spikeCol->Render();

	ImGui::SliderInt("BossHP", &_curHp, 0, _maxHp);
}

void Yggdrasil::Damaged(int damage)
{
	_curHp -= damage;

	if (_curHp < 0)
	{
		_curHp = 0;
		Dead();
	}
}

void Yggdrasil::Dead()
{
	DeActivate();
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

void Yggdrasil::MakeShared()
{
	_body = make_shared<Quad>(L"Resources/Texture/Boss/Yggdrasil/Body.png");

	_rightHand = make_shared<Quad>(L"Resources/Texture/Boss/Yggdrasil/rightHand.png");
	
	_leftHand = make_shared<Quad>(L"Resources/Texture/Boss/Yggdrasil/leftHand.png");

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
		result = _spikeCol->SideCollision(_player.lock()->GetBodyCollider());
		if (result.isHit)
			_player.lock()->Damaged(damage, result.dir);
	}
	else if (_isRightHand)
	{
		result = _rightHandCol->SideCollision(_player.lock()->GetBodyCollider());
		if (result.isHit)
			_player.lock()->Damaged(damage, result.dir);
	}
	else
	{
		result = _leftHandCol->SideCollision(_player.lock()->GetBodyCollider());
		if (result.isHit)
			_player.lock()->Damaged(damage, result.dir);
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

		HIT_RESULT result = _rightHandCol->Block(_player.lock()->GetFootCollider());
		if (result.dir == Direction::UP)
			_player.lock()->Ground();
	}
	else
	{
		_leftHand->GetTransform()->Move(SetLERP(_leftHand->GetTransform()->GetWorldPos(), _attackPos, DELTA_TIME * 8.0f));

		HIT_RESULT result = _leftHandCol->Block(_player.lock()->GetFootCollider());
		if (result.dir == Direction::UP)
			_player.lock()->Ground();
	}
}

void Yggdrasil::SpikeAttack()
{
	_spikeActive = true;
	_spikeUp = true;
	_spikeCol->GetTransform()->SetPos(Vector2(_spikePos.x, _spikePos.y - 300.0f));
	EFFECT->Play("Spike_15x1", _spikePos);
}

void Yggdrasil::SpikeFlipDir()
{
	_spikeUp = false;
}

void Yggdrasil::SpikeStop()
{
	_spikeActive = false;
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

void Yggdrasil::DeActivate()
{
	_rightBranchCol->DeActivate();
	_leftBranchCol->DeActivate();
	_headCol->DeActivate();
	_isAlive = false;
}