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
		switch (_curState)
		{
		case State::IDLE:
			SetIdle();
			break;
		case State::ATTACKREADY:
			AttackReady();
			break;
		case State::ATTACK:
			Attack();
			break;
		case State::AFTERATTACK:
			AfterAttack();
			break;
		case State::ATTACKEND:
			AttackReady();
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

		_curAttackDelay -= DELTA_TIME;
			
		if (_curAttackDelay <= 0.0f)
		{
			switch (_curState)
			{
			case State::IDLE:
				_curState = State::ATTACKREADY;
				_curAttackDelay = _maxAttackDelay;
				break;
			case State::ATTACKREADY:
				_curState = State::ATTACK;
				_attackPos.x = _player.lock()->GetFootCollider()->GetTransform()->GetPos().x;
				if (_attackPos.x > _body->GetTransform()->GetWorldPos().x)
				{
					_isRightHand = false;
					_leftHandCol->GetTransform()->Update();
					_leftHandCol->Activate();
				}
				else
				{
					_isRightHand = true;
					_rightHandCol->GetTransform()->Update();
					_rightHandCol->Activate();
				}
				_curAttackDelay = 0.25f;
				break;
			case State::ATTACK:
				_curState = State::AFTERATTACK;
				_curAttackDelay = _maxAttackDelay;
				break;
			case State::AFTERATTACK:
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

	_headCol = make_shared<CircleCollider>(150);
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

void Yggdrasil::AttackReady()
{
	Vector2 curPos = _rightHand->GetTransform()->GetWorldPos();
	Vector2 goalPos = Vector2(_originRightHandPos.x, _originRightHandPos.y + 300) - curPos;
	Vector2 distance = LERP(Vector2(0, 0), goalPos, DELTA_TIME * 2.0f);
	_rightHand->GetTransform()->Move(distance);

	curPos = _leftHand->GetTransform()->GetWorldPos();
	goalPos = Vector2(_originLeftHandPos.x, _originLeftHandPos.y + 300) - curPos;
	distance = LERP(Vector2(0, 0), goalPos, DELTA_TIME * 2.0f);
	_leftHand->GetTransform()->Move(distance);
}

void Yggdrasil::Attack()
{
	if (_isRightHand)
	{
		Vector2 curPos = _rightHand->GetTransform()->GetWorldPos();
		Vector2 goalPos = _attackPos - curPos;
		Vector2 distance = LERP(Vector2(0,0), Vector2(goalPos.x,goalPos.y + 100), DELTA_TIME * 8.0f);
		_rightHand->GetTransform()->Move(distance);

		if (_rightHandCol->IsCollision(_player.lock()->GetFootCollider()))
			_player.lock()->Damaged();
	}
	else
	{
		Vector2 curPos = _leftHand->GetTransform()->GetWorldPos();
		Vector2 goalPos = _attackPos - curPos;
		Vector2 distance = LERP(Vector2(0, 0), Vector2(goalPos.x, goalPos.y + 100), DELTA_TIME * 8.0f);
		_leftHand->GetTransform()->Move(distance);

		if (_leftHandCol->IsCollision(_player.lock()->GetFootCollider()))
			_player.lock()->Damaged();
	}
}

void Yggdrasil::AfterAttack()
{
	if (_isRightHand)
	{
		Vector2 curPos = _rightHand->GetTransform()->GetWorldPos();
		Vector2 goalPos = _attackPos - curPos;
		Vector2 distance = LERP(Vector2(0, 0), Vector2(goalPos.x, goalPos.y + 100), DELTA_TIME * 8.0f);
		_rightHand->GetTransform()->Move(distance);

		HIT_RESULT result = _rightHandCol->SideBlock(_player.lock()->GetFootCollider());
		if (result.dir == Direction::UP)
			_player.lock()->Ground();
	}
	else
	{
		Vector2 curPos = _leftHand->GetTransform()->GetWorldPos();
		Vector2 goalPos = _attackPos - curPos;
		Vector2 distance = LERP(Vector2(0, 0), Vector2(goalPos.x, goalPos.y + 100), DELTA_TIME * 8.0f);
		_leftHand->GetTransform()->Move(distance);

		HIT_RESULT result = _leftHandCol->SideBlock(_player.lock()->GetFootCollider());
		if (result.dir == Direction::UP)
			_player.lock()->Ground();
	}
}

void Yggdrasil::SetIdle()
{
	Vector2 curPos = _rightHand->GetTransform()->GetWorldPos();
	Vector2 goalPos = _originRightHandPos - curPos;
	Vector2 distance = LERP(Vector2(0, 0), goalPos, DELTA_TIME * 8.0f);
	_rightHand->GetTransform()->Move(distance);

	curPos = _leftHand->GetTransform()->GetWorldPos();
	goalPos = _originLeftHandPos - curPos;
	distance = LERP(Vector2(0, 0), goalPos, DELTA_TIME * 8.0f);
	_leftHand->GetTransform()->Move(distance);
}

void Yggdrasil::Idle()
{
	float curY = _body->GetTransform()->GetPos().y;
	float goalY;
	float speed;

	if (_up)
	{
		speed = 0.1f;
		goalY = _originBodyPos.y + 5.0f;
		if (curY >= goalY - 0.15f)
		{
			_up = false;
		}
	}
	else
	{
		speed = -0.1f;
		goalY = _originBodyPos.y - 5.0f;
		if (curY <= goalY + 0.15f)
		{
			_up = true;
		}
	}

	_body->GetTransform()->MoveY(speed);
}
