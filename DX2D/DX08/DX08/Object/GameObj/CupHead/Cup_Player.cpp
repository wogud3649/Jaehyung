#include "framework.h"
#include "Cup_Player.h"

using namespace tinyxml2;

Cup_Player::Cup_Player()
{
	CreatePath();
	CreateAction();
	_actions[_state]->Play();
}

Cup_Player::~Cup_Player()
{
}

void Cup_Player::Update()
{
	Movement();

	_sprites[State::IDLE]->Update();
	if (_state != State::IDLE)
		_sprites[_state]->Update();
	_actions[_state]->Update();
}

void Cup_Player::Render()
{
	_sprites[_state]->SetActionClip(_actions[_state]->GetCurClip());
	_sprites[_state]->Render();
}

void Cup_Player::SetAction(State state)
{
	if (_state == state)
		return;

	_actions[_state]->Reset();
	_state = state;
	_actions[_state]->Play();
}

shared_ptr<Transform> Cup_Player::GetTransform()
{
	return _sprites[State::IDLE]->GetTransform();
}

void Cup_Player::CreatePath()
{
	// PNG
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
}

void Cup_Player::CreateSprite(int w, int h, int index)
{
	shared_ptr<Sprite> sprite = make_shared<Sprite>(_spritePaths[index], Vector2(w, h));
	_sprites.push_back(sprite);
}

void Cup_Player::CreateAction()
{
	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	vector<Action::Clip> clips;
	string name;

	for (int i = 0; i < 5; i++)
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
		case State::IDLE:
			name = "CUP_IDLE";
			break;
		case State::RUN:
			name = "CUP_RUN";
			break;
		case State::JUMP:
			name = "CUP_JUMP";
			break;
		case State::DUCK:
			name = "CUP_DUCK";
			break;
		case State::DUCK_IDLE:
			name = "CUP_DUCK_IDLE";
			break;
		default:
			break;
		}
		_actions.push_back(make_shared<Action>(clips, name));
		clips.clear();
	}

	SetActionPos();
}

void Cup_Player::SetActionPos()
{
	for (auto sprite : _sprites)
	{
		if (sprite == _sprites[State::IDLE])
			continue;
		sprite->GetTransform()->SetParent(_sprites[State::IDLE]->GetTransform());
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
			SetAction(State::IDLE);
	}
	else if (KEY_PRESS('A'))
	{
		SetReverse(Direction::LEFT);
		if (!_isDuck)
		{
			_sprites[State::IDLE]->GetTransform()->GetPos().x -= _speed * DELTA_TIME;
			if (!_isJump)
				SetAction(State::RUN);
		}
	}
	else if (KEY_PRESS('D'))
	{
		SetReverse(Direction::RIGHT);
		if (!_isDuck)
		{
			_sprites[State::IDLE]->GetTransform()->GetPos().x += _speed * DELTA_TIME;
			if (!_isJump)
				SetAction(State::RUN);
		}
	}

	if (_isJump)
	{
		Jump();
		return;
	}

	if (KEY_UP('A') || KEY_UP('D'))
	{
		SetAction(State::IDLE);
	}

	if (KEY_DOWN('S'))
	{
		SetAction(State::DUCK);
	}
	if (KEY_PRESS('S'))
	{
		SetAction(State::DUCK_IDLE);
		_isDuck = true;
	}
	if (KEY_UP('S'))
	{
		SetAction(State::IDLE);
		_isDuck = false;
	}

	if (KEY_DOWN(VK_SPACE))
	{
		SetAction(State::JUMP);
		_isDuck = false;
		_isJump = true;
	}
}

void Cup_Player::Jump()
{
	_jumpSpeed -= 2000.0f * DELTA_TIME;
	_sprites[State::IDLE]->GetTransform()->GetPos().y += _jumpSpeed * DELTA_TIME;

	if (_sprites[State::IDLE]->GetTransform()->GetPos().y <= CENTER.y)
	{
		_sprites[State::IDLE]->GetTransform()->GetPos().y = CENTER.y;
		_isJump = false;
		_jumpSpeed = 1000.0f;
		SetAction(State::IDLE);
	}
}
