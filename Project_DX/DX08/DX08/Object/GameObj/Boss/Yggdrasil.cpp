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

	if (_isAttack)
		Attack();
	else
		SetIdle();

	if (_player.expired() == false)
	{
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
	}

	_curAttackCooldown -= DELTA_TIME;

	if (_curAttackCooldown <= 0.0f)
	{
		_curAfterAttackDelay -= DELTA_TIME;

		if (_isAttack == false)
		{
			if (_player.expired() == false)
			{
				_attackPos.x = _player.lock()->GetFootCollider()->GetTransform()->GetPos().x;
				if (_attackPos.x > _body->GetTransform()->GetWorldPos().x)
					_isRightHand = false;
				else
					_isRightHand = true;
			}
			_isAttack = true;
		}
	}

	if (_curAfterAttackDelay <= 0.0f)
	{
		_curAttackCooldown = _maxAttackCooldown;
		_curAfterAttackDelay = _maxAfterAttackDelay;
		_isAttack = false;
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
	ImGui::SliderFloat("AttackDelay", &_curAfterAttackDelay, 0, 3.0f);
	if (_player.expired() == false)
	{
		Vector2 pos = _player.lock()->GetFootCollider()->GetTransform()->GetWorldPos();
		ImGui::SliderFloat2("pos", (float*)&pos, 0, 99999);
	}

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
	_rightHandCol = make_shared<RectCollider>(Vector2(150, 180));
	_leftHandCol = make_shared<RectCollider>(Vector2(150, 170));
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
	_rightHandCol->GetTransform()->MoveY(-20);

	_leftHandCol->GetTransform()->MoveX(-20);
	_leftHandCol->GetTransform()->MoveY(-20);
}

void Yggdrasil::Attack()
{
	if (_isRightHand)
	{
		Vector2 curPos = _rightHand->GetTransform()->GetWorldPos();
		Vector2 goalPos = _attackPos - curPos;
		Vector2 distance = LERP(Vector2(0,0), Vector2(goalPos.x,goalPos.y + 100), DELTA_TIME * 8.0f);
		_rightHand->GetTransform()->Move(distance);
	}
	else
	{
		Vector2 curPos = _leftHand->GetTransform()->GetWorldPos();
		Vector2 goalPos = _attackPos - curPos;
		Vector2 distance = LERP(Vector2(0, 0), Vector2(goalPos.x, goalPos.y + 100), DELTA_TIME * 8.0f);
		_leftHand->GetTransform()->Move(distance);
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
