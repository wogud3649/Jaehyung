#include "framework.h"
#include "Yggdrasil.h"

Yggdrasil::Yggdrasil()
{
	MakeShared();
	SetParent();
	Adjust();
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
				break;
			case State::ATTACKAFTER:
				break;
			case State::ATTACKEND:
				break;
			default:
				break;
			}
			break;
		case Yggdrasil::SHOOT:
			break;
		default:
			break;
		}

		if (_player.lock()->GetJumpPower() <= 0.0f)
		{
			HIT_RESULT result;
			result = _rightBranchCol->TopBlock(_player.lock()->GetFootCollider());
			if (result.dir == Direction::UP)
				_player.lock()->Ground();
			result = _leftBranchCol->TopBlock(_player.lock()->GetFootCollider());
			if (result.dir == Direction::UP)
				_player.lock()->Ground();
		}

		if (_curAttackDelay > 0.0f)
			_curAttackDelay -= DELTA_TIME;
			
		if (_curState == State::ATTACK)
		{
			if ((_isRightHand && _rightHandCol->GetTransform()->GetWorldPos().y <= _attackPos.y + 10.0f) || (!_isRightHand && _leftHandCol->GetTransform()->GetWorldPos().y <= _attackPos.y + 10.0f))
			{
				_curState = State::ATTACKAFTER;
				_curAttackDelay = _maxAttackDelay;
			}
		}
		else if (_curAttackDelay <= 0.0f)
		{
			float curX;
			switch (_curState)
			{
			case State::IDLE:
				_curState = State::ATTACKREADY;
				_curAttackDelay = _maxAttackDelay;
				curX = _player.lock()->GetFootCollider()->GetTransform()->GetPos().x;
				if (curX > _body->GetTransform()->GetWorldPos().x)
					_isRightHand = false;
				else
					_isRightHand = true;
				break;
			case State::ATTACKREADY:
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
	}
}

void Yggdrasil::Render()
{
	if (_isAlive == false)
	{
		return;
	}

	_body->Render();

	_rightHand->Render();
	_leftHand->Render();

	_headCol->Render();
	_rightBranchCol->Render();
	_leftBranchCol->Render();
	_rightHandCol->Render();
	_leftHandCol->Render();
}

void Yggdrasil::PostRender()
{
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

	_rightHand->GetTransform()->UpdateSRT();
	_originRightHandPos = _rightHand->GetTransform()->GetWorldPos();
	_leftHand->GetTransform()->UpdateSRT();
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
}

void Yggdrasil::SetParent()
{
	_rightHand->GetTransform()->SetParent(_body->GetTransform());
	_leftHand->GetTransform()->SetParent(_body->GetTransform());

	_headCol->GetTransform()->SetParent(_body->GetTransform());
	_rightBranchCol->GetTransform()->SetParent(_body->GetTransform());
	_leftBranchCol->GetTransform()->SetParent(_body->GetTransform());
	_rightHandCol->GetTransform()->SetParent(_rightHand->GetTransform());
	_leftHandCol->GetTransform()->SetParent(_leftHand->GetTransform());
}

void Yggdrasil::Adjust()
{
	_rightHand->GetTransform()->MoveX(-350);
	_rightHand->GetTransform()->MoveY(-120);

	_leftHand->GetTransform()->MoveX(350);
	_leftHand->GetTransform()->MoveY(-120);

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

void Yggdrasil::StampAttackReady()
{
	_rightHand->GetTransform()->Move(SetLERP(_rightHand->GetTransform()->GetWorldPos(), Vector2(_originRightHandPos.x, _originRightHandPos.y + 300), DELTA_TIME * 2.0f));
	_leftHand->GetTransform()->Move(SetLERP(_leftHand->GetTransform()->GetWorldPos(), Vector2(_originLeftHandPos.x, _originLeftHandPos.y + 300), DELTA_TIME * 2.0f));
}

void Yggdrasil::StampAttack()
{
	int damage = rand() % (_maxDamage - _minDamage) + _minDamage;
	if (_isRightHand)
	{
		_rightHand->GetTransform()->Move(SetLERP(_rightHand->GetTransform()->GetWorldPos(), _attackPos, DELTA_TIME * 8.0f));

		HIT_RESULT result = _rightHandCol->SideCollision(_player.lock()->GetBodyCollider());
		if (result.isHit)
			_player.lock()->Damaged(damage, result.dir);
	}
	else
	{
		_leftHand->GetTransform()->Move(SetLERP(_leftHand->GetTransform()->GetWorldPos(), _attackPos, DELTA_TIME * 8.0f));

		HIT_RESULT result = _leftHandCol->SideCollision(_player.lock()->GetBodyCollider());
		if (result.isHit)
			_player.lock()->Damaged(damage, result.dir);
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

void Yggdrasil::SweepAttackReady()
{
	if (_isRightHand)
	{
		_rightHand->GetTransform()->Move(SetLERP(_rightHand->GetTransform()->GetWorldPos(), Vector2(_originRightHandPos.x + 1000, _attackPos.y), DELTA_TIME * 2.0f));
		_leftHand->GetTransform()->Move(SetLERP(_leftHand->GetTransform()->GetWorldPos(), Vector2(_originLeftHandPos.x + 100, _originLeftHandPos.y), DELTA_TIME * 2.0f));
	}
	else
	{
		_rightHand->GetTransform()->Move(SetLERP(_rightHand->GetTransform()->GetWorldPos(), Vector2(_originRightHandPos.x - 100, _originRightHandPos.y), DELTA_TIME * 2.0f));
		_leftHand->GetTransform()->Move(SetLERP(_leftHand->GetTransform()->GetWorldPos(), Vector2(_originLeftHandPos.x - 1000, _attackPos.y), DELTA_TIME * 2.0f));
	}
}

void Yggdrasil::SweepAttack()
{
}

void Yggdrasil::SweepAttackAfter()
{
}

void Yggdrasil::SweepAttackEnd()
{
}

void Yggdrasil::SetIdle()
{
	_rightHand->GetTransform()->Move(SetLERP(_rightHand->GetTransform()->GetWorldPos(), _originRightHandPos, DELTA_TIME * 8.0f));
	_leftHand->GetTransform()->Move(SetLERP(_leftHand->GetTransform()->GetWorldPos(), _originLeftHandPos, DELTA_TIME * 8.0f));
}

Vector2 Yggdrasil::SetLERP(Vector2 objPos, Vector2 targetPos, float speed)
{
	Vector2 curPos = objPos;
	Vector2 goalPos = targetPos - objPos;
	Vector2 distance = LERP(Vector2(0, 0), goalPos, speed);

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
}

void Yggdrasil::DeActivate()
{
	_rightBranchCol->DeActivate();
	_leftBranchCol->DeActivate();
	_headCol->DeActivate();
	_isAlive = false;
}
