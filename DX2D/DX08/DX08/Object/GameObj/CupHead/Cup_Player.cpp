#include "framework.h"
#include "Cup_Player.h"

using namespace tinyxml2;

Cup_Player::Cup_Player()
{
	CreateAction("Idle",Action::Type::LOOP);
	CreateAction("Run",Action::Type::LOOP);
	CreateAction("Jump",Action::Type::LOOP);
	CreateAction("Duck",Action::Type::END);
	CreateAction("DuckIdle",Action::Type::LOOP);
	CreateAction("AimStraightShot",Action::Type::END);
	_actions[State::CUP_AIM_STRAIGHT_SHOT]->SetCallBack(std::bind(&Cup_Player::SetIDLE,this));

	_transform = make_shared<Transform>();
	
	for (auto sprite : _sprites)
		sprite->GetTransform()->SetParent(_transform);

	 _transform->GetScale() *= 0.7f;

	_actions[_curState]->Play();
}

Cup_Player::~Cup_Player()
{
}

void Cup_Player::Update()
{
	Input();

	_sprites[_curState]->Update();
	_actions[_curState]->Update();

	_transform->UpdateSRT();
}

void Cup_Player::Render()
{
	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();
}

void Cup_Player::SetRight()
{
	if (_sprites[0]->GetLeftRight() == 0)
		return;
	for (auto sprite : _sprites)
		sprite->GetLeftRight() = 0;
}

void Cup_Player::SetLeft()
{
	if (_sprites[0]->GetLeftRight() == 1)
		return;
	for (auto sprite : _sprites)
		sprite->GetLeftRight() = 1;
}

void Cup_Player::Input()
{
	if (KEY_PRESS('A') && KEY_PRESS('D'))
	{
		if (!_isJump)
			SetAction(State::CUP_IDLE);
	}
	else if (KEY_PRESS('A'))
	{
		SetLeft();
		if (!_isDuck)
		{
			_transform->GetPos().x -= _speed * DELTA_TIME;
			if (!_isJump)
				SetAction(State::CUP_RUN);
		}
	}
	else if (KEY_PRESS('D'))
	{
		SetRight();
		if (!_isDuck)
		{
			_transform->GetPos().x += _speed * DELTA_TIME;
			if (!_isJump)
				SetAction(State::CUP_RUN);
		}
	}
	if (KEY_UP('A') || KEY_UP('D'))
	{
		if (!_isDuck && !_isJump)
			SetAction(State::CUP_IDLE);
	}

	if (KEY_DOWN('S'))
	{
		if (!_isJump)
			SetAction(State::CUP_DUCK);
		//TODO
	}
	if (KEY_PRESS('S'))
	{
		if (!_isJump)
			SetAction(State::CUP_DUCK_IDLE);
	}
	if (KEY_UP('S'))
	{
		if (!_isJump)
			SetAction(State::CUP_IDLE);
	}

	if (_curState == State::CUP_DUCK_IDLE)
		_isDuck = true;
	else
		_isDuck = false;

	if (KEY_DOWN(VK_SPACE))
	{
		if (!_isJump)
		{
			_isJump = true;
			_floorHeight = _transform->GetPos().y;
			SetAction(State::CUP_JUMP);
		}
	}

	if (!_isDuck)
	{
		if (_isJump)
		{
			Jump();
		}
	}

	if (KEY_DOWN(VK_LBUTTON))
	{
		if (!_isDuck && !_isJump)
			Shot();
	}
}

void Cup_Player::Jump()
{
	_jumpSpeed -= 2000.0f * DELTA_TIME;
	_transform->GetPos().y += _jumpSpeed * DELTA_TIME;

	if (_transform->GetPos().y <= _floorHeight)
	{
		_transform->GetPos().y = _floorHeight;
		_isJump = false;
		_jumpSpeed = 1000.0f;
		SetAction(State::CUP_IDLE);
	}
}

void Cup_Player::Shot()
{
	SetAction(State::CUP_AIM_STRAIGHT_SHOT);
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
	wstring wName = wstring(name.begin(), name.end());
	wstring srvPath = L"Resource/Texture/CupHead/" + wName + L".png";
	shared_ptr<SRV> srv = SRV_ADD(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	string path = "Resource/XML/" + name + ".xml";
	document->LoadFile(path.c_str());

	XMLElement* textureAtlas = document->FirstChildElement();
	XMLElement* row = textureAtlas->FirstChildElement();

	vector<Action::Clip> clips;

	float wAverage = 0;
	float hAverage = 0;

	int count = 0;

	while (true)
	{
		if (row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		clips.emplace_back(x, y, w, h, srv);

		wAverage += w;
		hAverage += h;
		count++;

		row = row->NextSiblingElement();
	}

	wAverage /= count;
	hAverage /= count;
	
	string actionName = "CUP_" + name;
	_actions.emplace_back(make_shared<Action>(clips, name, type, 0.1f));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, Vector2(wAverage, hAverage)));
}