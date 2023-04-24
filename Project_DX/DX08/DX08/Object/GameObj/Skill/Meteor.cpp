#include "framework.h"
#include "Meteor.h"

Meteor::Meteor()
{
	
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
	if (_isActive == false)
		return;

	for (auto quad : _quads)
		quad->Update();

	for (auto col : _cols)
		col->Update();

	for (auto quad : _quads)
	{
		quad->GetTransform()->MoveX(_speed);
		quad->GetTransform()->MoveY(_curJumpPower);
	}

	_curJumpPower -= DELTA_TIME;
	_curDuration -= DELTA_TIME;

	if (_curDuration < 0)
	{
		DeActivate();
	}
}

void Meteor::Render()
{
	if (_isActive == false)
		return;

	for (auto quad : _quads)
		quad->Render();

	for (auto col : _cols)
		col->Render();
}

void Meteor::SetActive()
{
	Skill::SetActive();

	for (auto col : _cols)
		col->Activate();
}

void Meteor::SetRandomSpeeds()
{
	for (auto speed : _speeds)
	{
		speed = rand() % 100;
		int sign = rand() % 2;
		if (sign == 1)
			speed *= -1;
	}
}

void Meteor::Hit()
{
	DeActivate();
}

void Meteor::DeActivate()
{
	Skill::DeActivate();

	_curDuration = _maxDuration;
	_curJumpPower = _maxJumpPower;

	for (auto quad : _quads)
		quad->GetTransform()->SetPos(Vector2(0, 0));

	for (auto col : _cols)
		col->DeActivate();
}