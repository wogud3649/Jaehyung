#include "framework.h"
#include "Cup_Player.h"

using namespace tinyxml2;

Cup_Player::Cup_Player()
{
	Init();
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

	for (auto bullet : _bullets)
		bullet->Update();
}

void Cup_Player::Render()
{
	for (auto bullet : _bullets)
		bullet->Render();

	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();
}

void Cup_Player::SetRight()
{
	if (_dir == 0)
		return;
	_dir = 0;
	for (auto sprite : _sprites)
		sprite->GetLeftRight() = _dir;
}

void Cup_Player::SetLeft()
{
	if (_dir == 1)
		return;
	_dir = 1;
	for (auto sprite : _sprites)
		sprite->GetLeftRight() = _dir;
}

void Cup_Player::Input()
{
	if (_isShooting)
		return;

	if (KEY_PRESS('A') && KEY_PRESS('D'))
	{
		if (!_isJump && !_isDuck)
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
		{
			_isDucking = true;
			SetAction(State::CUP_DUCK);
			_actions[State::CUP_DUCK]->SetCallBack(std::bind(&Cup_Player::SetDuckIDLE, this));
		}
	}
	if (KEY_PRESS('S'))
	{
		if (!_isJump && !_isDucking)
			SetAction(State::CUP_DUCK_IDLE);
	}
	if (KEY_UP('S'))
	{
		if (!_isJump)
			SetAction(State::CUP_IDLE);
	}

	if (_curState == State::CUP_DUCK || _curState == State::CUP_DUCK_IDLE)
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
		{
			Shot();
		}
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
	auto iter = find_if(_bullets.begin(), _bullets.end(), [](const shared_ptr<Cup_Bullet>& a)->bool
		{
			return a->GetActive() == false;
		});
	if (iter != _bullets.end())
	{
		(*iter)->GetTransform()->GetPos() = _transform->GetPos();
		(*iter)->SetDirection(_dir);
		(*iter)->SetActive(true);
		_actions[State::CUP_AIM_STRAIGHT_SHOT]->SetCallBack(std::bind(&Cup_Player::SetIDLE, this));
		SetAction(State::CUP_AIM_STRAIGHT_SHOT);
		_isShooting = true;
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
	_isShooting = false;
}

void Cup_Player::SetDuckIDLE()
{
	_isDucking = false;
}

void Cup_Player::Init()
{
	CreateAction("Idle", Action::Type::LOOP);
	CreateAction("Run", Action::Type::LOOP);
	CreateAction("Jump", Action::Type::LOOP);
	CreateAction("Duck", Action::Type::END);
	CreateAction("DuckIdle", Action::Type::LOOP);
	CreateAction("AimStraightShot", Action::Type::END);
	
	_transform = make_shared<Transform>();

	for (int i = 0; i < bulletSize; i++)
		_bullets.emplace_back(make_shared<Cup_Bullet>());

	for (auto sprite : _sprites)
		sprite->GetTransform()->SetParent(_transform);

	_transform->GetScale() *= 0.7f;

	_actions[_curState]->Play();
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