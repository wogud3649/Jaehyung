#include "framework.h"
#include "Meteor.h"

Meteor::Meteor()
{
	_power = 30.0f;

	for (int i = 0; i < 3; i++)
	{
		shared_ptr<Quad> quad = make_shared<Quad>(L"Resources/Texture/Effect/Wizard/Meteor/Meteor.png");
		quad->GetTransform()->SetParent(_transform);
		_quads.emplace_back(quad);
	}

	for (int i = 0; i < 3; i++)
	{
		shared_ptr<CircleCollider> col = make_shared<CircleCollider>(29);
		col->DeActivate();
		_cols.emplace_back(col);
	}

	_cols[0]->GetTransform()->SetParent(_quads[0]->GetTransform());
	_cols[1]->GetTransform()->SetParent(_quads[1]->GetTransform());
	_cols[2]->GetTransform()->SetParent(_quads[2]->GetTransform());
}

Meteor::~Meteor()
{
}

void Meteor::Update()
{
	int _curActive = 0;
	for (auto isActive : _isActives)
	{
		if (isActive)
			_curActive++;
	}
	if (_curActive == 0)
	{
		DeActivateAll();
		return;
	}

	for (int i = 0; i < 3; i++)
	{
		if (_isActives[i])
		{
			_quads[i]->Update();
			_cols[i]->Update();
		}
	}

	for (int i = 0; i < 3; i++)
	{
		_quads[i]->GetTransform()->MoveX(_speeds[i] * DELTA_TIME);
		_quads[i]->GetTransform()->MoveY(_curJumpPower * DELTA_TIME);
	}

	if (_curJumpPower > 0)
	{
		if (_curJumpPower - GRAVITY * GRAVITY * DELTA_TIME < 0)
			SOUND->Play("Wizard_Meteor_Falling");
	}
	_curJumpPower -= GRAVITY * GRAVITY * DELTA_TIME;
	_curDuration -= DELTA_TIME;

	if (_curDuration < 0)
	{
		DeActivateAll();
	}
}

void Meteor::Render()
{
	for (int i = 0; i < 3; i++)
	{
		if (_isActives[i])
		{
			_quads[i]->Render();
			_cols[i]->Render();
		}
	}
}

void Meteor::SetActive()
{
	_curDuration = _maxDuration;
	_curJumpPower = _maxJumpPower;

	for (int i = 0; i < 3; i++)
	{
		_quads[i]->GetTransform()->SetPos(Vector2(0, 0));
		_quads[i]->Update();
		_cols[i]->GetTransform()->Update();
	}

	for (auto isActive : _isActives)
		isActive = true;

	for (auto col : _cols)
		col->Activate();
}

void Meteor::SetRandomSpeeds()
{
	for (int i = 0; i < 3; i++)
	{
		int speed = rand() % 200;
		int sign = rand() % 2;
		if (sign == 1)
			speed *= -1;

		_speeds[i] = speed;
	}
}

void Meteor::Hit(int index)
{
	DeActivate(index);
}

void Meteor::DeActivate(int index)
{
	_cols[index]->DeActivate();

	_isActives[index] = false;
}

void Meteor::DeActivateAll()
{
	for (int i = 0; i < 3; i++)
	{
		_cols[i]->DeActivate();
		_isActives[i] = false;
	}
}