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
	if (KEY_PRESS('D'))
	{
		SetAction(State::RUN);
	}
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
	_state = state;
	_curAction = _actions[_state];
	if (_oldAction != nullptr && _curAction->GetName() != _oldAction->GetName())
	{
		_oldAction->Reset();
		_actions[_state]->Play();
	}
	_oldAction = _actions[_state];
}

shared_ptr<Transform> Cup_Player::GetTransform()
{
	return _sprites[State::IDLE]->GetTransform();
}

void Cup_Player::CreatePath()
{
	// PNG
	wstring path = L"Resource/Texture/CupHead/Idle.png";
	_spritePaths.push_back(path);

	path = L"Resource/Texture/CupHead/Run.png";
	_spritePaths.push_back(path);
	
	// XML
	string xmlPath = "Resource/XML/Idle.xml";
	_xmlPaths.push_back(xmlPath);

	xmlPath = "Resource/XML/Run.xml";
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

	for (int i = 0; i < 2; i++)
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
