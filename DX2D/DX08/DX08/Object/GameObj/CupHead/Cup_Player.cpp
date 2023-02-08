#include "framework.h"
#include "Cup_Player.h"

using namespace tinyxml2;

Cup_Player::Cup_Player()
{
	CreateAction("Idle", Action::Type::LOOP);
	CreateAction("Run", Action::Type::LOOP);
	CreateAction("AimStraightShot", Action::Type::END);
	CreateAction("Jump", Action::Type::LOOP);
	
	_col = make_shared<CircleCollider>(73);

	_transform = _col->GetTransform();

	for (auto sprite : _sprites)
		sprite->GetTransform()->SetParent(_transform);

	_col->GetTransform()->GetScale() *= 0.7f;

	_oldState = State::CUP_IDLE;
	_actions[State::CUP_IDLE]->Play();
}

Cup_Player::~Cup_Player()
{
	_transform = nullptr;
}

void Cup_Player::Update()
{
	Input();

	for (auto sprite : _sprites)
		sprite->Update();

	for (auto action : _actions)
		action->Update();

	_col->Update();
}

void Cup_Player::Render()
{
	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();
	_col->Render();
}

void Cup_Player::SetRight()
{
	_isRight = true;

	for (auto sprite : _sprites)
	{
		sprite->GetLeftRight() = 0;
	}
}

void Cup_Player::SetLeft()
{
	_isRight = false;

	for (auto sprite : _sprites)
	{
		sprite->GetLeftRight() = 1;
	}
}

void Cup_Player::Input()
{
	if (KEY_PRESS('A'))
	{
		_col->GetTransform()->GetPos().x -= _speed * DELTA_TIME;
		if (_curState != State::CUP_JUMP)
			SetAction(State::CUP_RUN);

		SetLeft();
	}

	if (KEY_PRESS('D'))
	{
		_col->GetTransform()->GetPos().x += _speed * DELTA_TIME;
		if (_curState != State::CUP_JUMP)
			SetAction(State::CUP_RUN);

		SetRight();
	}

	if (KEY_UP('A') || KEY_UP('D'))
	{
		if (_curState != State::CUP_JUMP)
			SetAction(State::CUP_IDLE);
	}
}

void Cup_Player::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Cup_Player::SetIDLE()
{
	SetAction(State::CUP_IDLE);
}

void Cup_Player::CreateAction(string name, Action::Type type)
{
	// idle.png
	string xmlPath = "Resource/XML/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "CUP_" + name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}
