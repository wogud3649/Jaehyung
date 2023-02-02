#include "framework.h"
#include "Cup_Player.h"

using namespace tinyxml2;

Cup_Player::Cup_Player()
{
	CreateAction();
	_actions[_state]->Play();
	_actions[State::CUP_AIM_STRAIGHT_SHOT]->SetCallBack(std::bind(&Cup_Player::SetIDLE,this));

	//_transform = make_shared<Transform>();
	//for (auto sprite : _sprites)
	//	sprite->GetTransform()->SetParent(_transform);
	// _transform->GetScale() *= 0.7f;
}

Cup_Player::~Cup_Player()
{
}

void Cup_Player::Update()
{
	Movement();

	_sprites[State::CUP_IDLE]->Update();
	if (_state != State::CUP_IDLE)
		_sprites[_state]->Update();
	_actions[_state]->Update();

	//_transform->UpdateSRT();
}

void Cup_Player::Render()
{
	_sprites[_state]->SetActionClip(_actions[_state]->GetCurClip());
	_sprites[_state]->Render();
}

void Cup_Player::SetRight()
{
	for (auto sprite : _sprites)
		sprite->GetLeftRight() = 0;
}

void Cup_Player::SetLeft()
{
	for (auto sprite : _sprites)
		sprite->GetLeftRight() = 1;
}

void Cup_Player::SetAction(State state)
{
	if (_state == state)
		return;

	_actions[_state]->Reset();
	_state = state;
	_actions[_state]->Play();
}

void Cup_Player::SetIDLE()
{
	SetAction(State::CUP_IDLE);
}

shared_ptr<Transform> Cup_Player::GetTransform()
{
	//return _transform;
	return _sprites[State::CUP_IDLE]->GetTransform();
}

void Cup_Player::CreatePath()
{
	// PNG
	// wstring wName = wstring(name.begin(), name.end());
	// TODO
	wstring pngStd = L"Resource/Texture/CupHead/";
	wstring path = pngStd + L"Idle.png";
	_spritePaths.push_back(path);

	path = pngStd + L"Run.png";
	_spritePaths.push_back(path);

	path = pngStd + L"Jump.png";
	_spritePaths.push_back(path);

	path = pngStd + L"Duck.png";
	_spritePaths.push_back(path);

	path = pngStd + L"DuckIdle.png";
	_spritePaths.push_back(path);

	path = pngStd + L"AimStraightShot.png";
	_spritePaths.push_back(path);
	
	// XML
	string xmlStd = "Resource/XML/";
	string xmlPath = xmlStd + "Idle.xml";
	_xmlPaths.push_back(xmlPath);

	xmlPath = xmlStd + "Run.xml";
	_xmlPaths.push_back(xmlPath);

	xmlPath = xmlStd + "Jump.xml";
	_xmlPaths.push_back(xmlPath);

	xmlPath = xmlStd + "Duck.xml";
	_xmlPaths.push_back(xmlPath);

	xmlPath = xmlStd + "DuckIdle.xml";
	_xmlPaths.push_back(xmlPath);

	xmlPath = xmlStd + "AimStraightShot.xml";
	_xmlPaths.push_back(xmlPath);
}

void Cup_Player::CreateSprite(int w, int h, int index)
{
	shared_ptr<Sprite> sprite = make_shared<Sprite>(_spritePaths[index], Vector2(w, h));
	_sprites.push_back(sprite);
}

void Cup_Player::CreateAction()
{
	CreatePath();
	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	vector<Action::Clip> clips;
	Action::Type type;
	string name;

	for (int i = 0; i < 6; i++)
	{
		float totalW = 0;
		float totalH = 0;
		int count = 0;
		document->LoadFile(_xmlPaths[i].c_str());

		XMLElement* textureAtlas = document->FirstChildElement();
		XMLElement* row = textureAtlas->FirstChildElement();
		shared_ptr<SRV> srv = SRV_ADD(_spritePaths[i]);

		while (true)
		{
			if (row == nullptr)
				break;

			int x = row->FindAttribute("x")->IntValue();
			int y = row->FindAttribute("y")->IntValue();
			int w = row->FindAttribute("w")->IntValue();
			int h = row->FindAttribute("h")->IntValue();
			totalW += w;
			totalH += h;
			count++;

			clips.emplace_back(x, y, w, h, srv);

			row = row->NextSiblingElement();
		}

		CreateSprite(totalW / count, totalH / count, i);

		switch (i)
		{
		case State::CUP_IDLE:
			name = "CUP_IDLE";
			type = Action::LOOP;
			break;
		case State::CUP_RUN:
			name = "CUP_RUN";
			type = Action::LOOP;
			break;
		case State::CUP_JUMP:
			name = "CUP_JUMP";
			type = Action::LOOP;
			break;
		case State::CUP_DUCK:
			name = "CUP_DUCK";
			type = Action::END;
			break;
		case State::CUP_DUCK_IDLE:
			name = "CUP_DUCK_IDLE";
			type = Action::LOOP;
			break;
		case State::CUP_AIM_STRAIGHT_SHOT:
			name = "CUP_AIM_STRAIGHT_SHOT";
			type = Action::END;
		default:
			break;
		}
		_actions.emplace_back(make_shared<Action>(clips, name, type, 0.1f));
		clips.clear();
	}

	SetActionPos();
}

void Cup_Player::SetActionPos()
{
	for (auto sprite : _sprites)
	{
		if (sprite == _sprites[State::CUP_IDLE])
			continue;
		sprite->GetTransform()->SetParent(_sprites[State::CUP_IDLE]->GetTransform());
	}
}

void Cup_Player::SetReverse(Direction dir)
{
	if (_dir == dir)
		return;

	for (auto sprite : _sprites)
		sprite->SetReverse();
	_dir = dir;
}

void Cup_Player::Movement()
{
	if (KEY_PRESS('A') && KEY_PRESS('D'))
	{
		if (!_isJump && !_isDuck)
			SetAction(State::CUP_IDLE);
	}
	else if (KEY_PRESS('A'))
	{
		SetReverse(Direction::LEFT);
		if (!_isDuck)
		{
			_sprites[State::CUP_IDLE]->GetTransform()->GetPos().x -= _speed * DELTA_TIME;
			if (!_isJump)
				SetAction(State::CUP_RUN);
		}
	}
	else if (KEY_PRESS('D'))
	{
		SetReverse(Direction::RIGHT);
		if (!_isDuck)
		{
			_sprites[State::CUP_IDLE]->GetTransform()->GetPos().x += _speed * DELTA_TIME;
			if (!_isJump)
				SetAction(State::CUP_RUN);
		}
	}

	if (_isJump)
	{
		Jump();
		return;
	}

	if (KEY_UP('A') || KEY_UP('D'))
	{
		SetAction(State::CUP_IDLE);
	}

	if (KEY_DOWN('S'))
	{
		SetAction(State::CUP_DUCK);
		//TODO
	}
	if (KEY_PRESS('S'))
	{
		SetAction(State::CUP_DUCK_IDLE);
		_isDuck = true;
	}
	if (KEY_UP('S'))
	{
		SetAction(State::CUP_IDLE);
		_isDuck = false;
	}

	if (KEY_DOWN(VK_SPACE))
	{
		SetAction(State::CUP_JUMP);
		_isDuck = false;
		_isJump = true;
	}

	Shot();
}

void Cup_Player::Input()
{
	// TODO
}

void Cup_Player::Jump()
{
	_jumpSpeed -= 2000.0f * DELTA_TIME;
	_sprites[State::CUP_IDLE]->GetTransform()->GetPos().y += _jumpSpeed * DELTA_TIME;

	if (_sprites[State::CUP_IDLE]->GetTransform()->GetPos().y <= CENTER.y)
	{
		_sprites[State::CUP_IDLE]->GetTransform()->GetPos().y = CENTER.y;
		_isJump = false;
		_jumpSpeed = 1000.0f;
		SetAction(State::CUP_IDLE);
	}
}

void Cup_Player::Shot()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		SetAction(State::CUP_AIM_STRAIGHT_SHOT);
	}
}
