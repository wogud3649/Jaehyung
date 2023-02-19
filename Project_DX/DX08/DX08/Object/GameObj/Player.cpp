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
	int frame;
	Action::Type type;

	for (int i = 0; i < State::StateSize; i++)
	{
		switch (i)
		{
		case 0:
			state = "IDLE";
			frame = 4;
			type = Action::Type::LOOP;
			sortX = MyXML::Sort::RIGHT;
			sortY = MyXML::Sort::BOTTOM;
			break;
		case 1:
			state = "WALK";
			frame = 8;
			type = Action::Type::LOOP;
			sortX = MyXML::Sort::RIGHT;
			sortY = MyXML::Sort::BOTTOM;
			break;
		case 2:
			state = "JUMP";
			frame = 2;
			type = Action::Type::END;
			sortX = MyXML::Sort::RIGHT;
			sortY = MyXML::Sort::BOTTOM;
			break;
		case 3:
			state = "DASH";
			frame = 1;
			type = Action::Type::END;
			sortX = MyXML::Sort::RIGHT;
			sortY = MyXML::Sort::BOTTOM;
			break;
		case 4:
			state = "ATTACKA";
			frame = 5;
			type = Action::Type::END;
			sortX = MyXML::Sort::LEFT;
			sortY = MyXML::Sort::MIDDLE;
		case 5:
			state = "ATTACKB";
			frame = 4;
			type = Action::Type::END;
			sortX = MyXML::Sort::LEFT;
			sortY = MyXML::Sort::MIDDLE;
		default:
			break;
		}
		wstring stateW(state.begin(), state.end());

		wstring srvPath = L"Resources/Texture/" + skulTypeW + L"/" + stateW + L".png";
		string xmlPath = "Resources/XML/" + skulType + "/" + state + ".xml";

		MyXML xml = MyXML(xmlPath, srvPath);

		_actions[_skulType].emplace_back(make_shared<Action>(xml.GetClips(sortX, sortY)));

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
