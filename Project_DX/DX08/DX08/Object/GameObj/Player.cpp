#include "framework.h"
#include "Player.h"

Player::Player()
{
	_sprites.resize(SkulType::SkulTypeSize);
	_actions.resize(SkulType::SkulTypeSize);
	CreateAction(SkulType::SKUL);
	CreateAction(SkulType::HEADLESS);
	CreateAction(SkulType::PIKE);

	_footCol = make_shared<CircleCollider>(15);

	_bodyCol = make_shared<CircleCollider>(15);
	_bodyCol->GetTransform()->SetParent(_footCol->GetTransform());
	_bodyCol->GetTransform()->MoveY(20.0f);

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
	_footCol->Update();

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
	_footCol->Render();
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
	case Player::PIKE:
		skulType = "PIKE";
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
			speed = 0.15f;
			sortX = MyXML::Sort::RIGHT;
			sortY = MyXML::Sort::BOTTOM;
			break;
		case 4:
			state = "FALL";
			type = Action::Type::END;
			speed = 0.1f;
			sortX = MyXML::Sort::MIDDLE;
			sortY = MyXML::Sort::MIDDLE;
			break;
		case 5:
			state = "FALLREPEAT";
			type = Action::Type::LOOP;
			speed = 0.1f;
			sortX = MyXML::Sort::MIDDLE;
			sortY = MyXML::Sort::MIDDLE;
			break;
		case 6:
			state = "ATTACKA";
			type = Action::Type::END;
			speed = _attackSpeed;
			sortX = MyXML::Sort::MIDDLE;
			sortY = MyXML::Sort::MIDDLE;
			break;
		case 7:
			state = "ATTACKB";
			type = Action::Type::END;
			speed = _attackSpeed;
			sortX = MyXML::Sort::MIDDLE;
			sortY = MyXML::Sort::MIDDLE;
			break;
		case 8:
			state = "JUMPATTACK";
			type = Action::Type::END;
			speed = _attackSpeed;
			sortX = MyXML::Sort::MIDDLE;
			sortY = MyXML::Sort::MIDDLE;
			break;
		case 9:
			state = "SKILL";
			type = Action::Type::END;
			speed = 0.1f;
			sortX = MyXML::Sort::MIDDLE;
			sortY = MyXML::Sort::MIDDLE;
			break;
		default:
			break;
		}
		if (_skulType == SkulType::HEADLESS)
			state = "IDLE";
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