#include "framework.h"
#include "Player.h"

Player::Player()
{
	_sprites.resize(SkulType::SkulTypeSize);
	_actions.resize(SkulType::SkulTypeSize);
	CreateAction(SkulType::SKUL);
	CreateAction(SkulType::HEADLESS);

	_bodyCol = make_shared<CircleCollider>(30);

	for (auto row : _sprites)
		for (auto sprite : row)
			sprite->GetTransform()->SetParent(_bodyCol->GetTransform());

	_actions[SkulType::SKUL][State::IDLE]->Play();
}

Player::~Player()
{
}

void Player::Update()
{
	_bodyCol->Update();

	for (auto sprite : _sprites[_curSkul])
		sprite->Update();

	for (auto action : _actions[_curSkul])
		action->Update();
}

void Player::Render()
{
	_sprites[_curSkul][_curState]->SetActionClip(_actions[_curSkul][_curState]->GetCurClip());
	_sprites[_curSkul][_curState]->Render();
	_bodyCol->Render();
}

void Player::CreateAction(SkulType _skulType)
{
	MyXML::Sort sortX;
	MyXML::Sort sortY;
	string skulType;
	switch (_skulType)
	{
	case Player::SKUL:
		skulType = "SKUL";
		break;
	case Player::HEADLESS:
		skulType = "HEADLESS";
		break;
	default:
		break;
	}

	wstring skulTypeW(skulType.begin(), skulType.end());
	string state;
	string name;
	Action::Type type;
	float speed;

	for (int i = 0; i < State::StateSize; i++)
	{
		switch (i)
		{
		case 0:
			state = "IDLE";
			type = Action::Type::LOOP;
			speed = 0.1f;
			sortX = MyXML::Sort::RIGHT;
			sortY = MyXML::Sort::BOTTOM;
			break;
		case 1:
			state = "WALK";
			type = Action::Type::LOOP;
			speed = 0.1f;
			sortX = MyXML::Sort::RIGHT;
			sortY = MyXML::Sort::BOTTOM;
			break;
		case 2:
			state = "JUMP";
			type = Action::Type::END;
			speed = 0.1f;
			sortX = MyXML::Sort::RIGHT;
			sortY = MyXML::Sort::BOTTOM;
			break;
		case 3:
			state = "DASH";
			type = Action::Type::END;
			speed = 0.2f;
			sortX = MyXML::Sort::RIGHT;
			sortY = MyXML::Sort::BOTTOM;
			break;
		case 4:
			state = "ATTACKA";
			type = Action::Type::END;
			speed = 0.1f;
			sortX = MyXML::Sort::LEFT;
			sortY = MyXML::Sort::MIDDLE;
		default:
			break;
		}
		wstring stateW(state.begin(), state.end());

		wstring srvPath = L"Resources/Texture/" + skulTypeW + L"/" + stateW + L".png";
		string xmlPath = "Resources/XML/" + skulType + "/" + state + ".xml";

		MyXML xml = MyXML(xmlPath, srvPath);

		name = skulType + "_" + state;

		_actions[_skulType].emplace_back(make_shared<Action>(xml.GetClips(sortX, sortY), name, type, speed));

		Vector2 maxSize = xml.MaxSize() * 2.0f;
		shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, maxSize);
		_sprites[_skulType].emplace_back(sprite);
	}
}

void Player::SetAction(State state)
{
	_curState = state;
	if (_curState == _oldState)
		return;

	_sprites[_curSkul][_curState]->SetDirection(_direction);
	_actions[_curSkul][_curState]->Play();
	_actions[_curSkul][_oldState]->Reset();
	_oldState = _curState;
}

void Player::SetSkul(SkulType skulType)
{
	_curSkul = skulType;
	if (_curSkul == _oldSkul)
		return;
	if (_curState != State::IDLE)
		_curState = State::IDLE;

	_sprites[_curSkul][_curState]->SetDirection(_direction);
	_actions[_curSkul][_curState]->Play();
	_actions[_oldSkul][_oldState]->Reset();
	_oldState = _curState;
	_oldSkul = _curSkul;
}
