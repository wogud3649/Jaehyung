#include "framework.h"
#include "Player.h"

Player::Player()
{
	CreateAction(SkulType::SKUL, State::IDLE, Action::Type::LOOP);
	CreateAction(SkulType::SKUL, State::WALK, Action::Type::LOOP, MyXML::Sort::MIDDLE);
	CreateAction(SkulType::SKUL, State::ATTACKA, Action::Type::END, MyXML::Sort::LEFT, MyXML::Sort::MIDDLE);
	CreateAction(SkulType::SKUL, State::SKILL, Action::Type::END, MyXML::Sort::LEFT, MyXML::Sort::BOTTOM);

	_col = make_shared<CircleCollider>(30);

	for (auto sprite : _sprites)
		sprite->GetTransform()->SetParent(_col->GetTransform());

	_actions[State::IDLE]->Play();
}

Player::~Player()
{
}

void Player::Update()
{
	Input();

	_col->Update();

	for (auto sprite : _sprites)
		sprite->Update();

	for (auto action : _actions)
		action->Update();
}

void Player::Render()
{
	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();
	_col->Render();
}

void Player::CreateAction(SkulType skulType, State state, Action::Type type, MyXML::Sort sortx, MyXML::Sort sorty)
{
	string _skulType;
	string _state;

	switch (skulType)
	{
	case Player::SKUL:
		_skulType = "SKUL";
		break;
	case Player::HEADLESS:
		_skulType = "HEADLESS";
		break;
	default:
		break;
	}

	switch (state)
	{
	case Player::IDLE:
		_state = "IDLE";
		break;
	case Player::WALK:
		_state = "WALK";
		break;
	case Player::ATTACKA:
		_state = "ATTACKA";
		break;
	case Player::SKILL:
		_state = "SKILL";
		break;
	default:
		break;
	}

	wstring _skulTypeW(_skulType.begin(), _skulType.end());
	wstring _stateW(_state.begin(), _state.end());

	string xmlPath = "Resources/XML/" + _skulType + "/" + _state + ".xml";
	wstring srvPath = L"Resources/Texture/" + _skulTypeW + L"/" + _stateW + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = _skulType + "_" + _state;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(sortx, sorty), actionName, type));

	Vector2 maxSize = xml.MaxSize() * 2.0f;
	_sprites.emplace_back(make_shared<Sprite>(srvPath, maxSize));
}

void Player::SetAction(State state)
{
	_curState = state;
	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Player::Input()
{
	if (KEY_PRESS('D'))
	{
		_sprites[_curState]->SetDirection(Direction::RIGHT);
		SetAction(State::WALK);
		GetTransform()->MoveX(_speed * DELTA_TIME);
	}
	if (KEY_PRESS('A'))
	{
		_sprites[_curState]->SetDirection(Direction::LEFT);
		SetAction(State::WALK);
		GetTransform()->MoveX(-_speed * DELTA_TIME);
	}
	if (KEY_UP('D'))
	{
		SetAction(State::IDLE);
	}
	if (KEY_UP('A'))
	{
		SetAction(State::IDLE);
	}
	if (KEY_DOWN(VK_LBUTTON))
	{
		SetAction(State::ATTACKA);
		_actions[_curState]->SetCallBack(std::bind(&Player::SetIdle, this));
	}
	if (KEY_DOWN(VK_RBUTTON))
	{
		SetAction(State::SKILL);
		_actions[_curState]->SetCallBack(std::bind(&Player::SetIdle, this));
	}
}

void Player::SetIdle()
{
	SetAction(State::IDLE);
}
