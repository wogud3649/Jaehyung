#include "framework.h"
#include "Cup_Player.h"

using namespace tinyxml2;

Cup_Player::Cup_Player()
{
	wstring srvPath = L"Resource/Texture/CupHead/Idle.png";
	CreateAction();
	_action->Play();
}

Cup_Player::~Cup_Player()
{
}

void Cup_Player::Update()
{
	_sprite->Update();
	_action->Update();
}

void Cup_Player::Render()
{
	_sprite->SetActionClip(_action->GetCurClip());
	_sprite->Render();
}

void Cup_Player::CreateAction()
{
	wstring srvPath = L"Resource/Texture/CupHead/Idle.png";
	shared_ptr<SRV> srv = SRV_ADD(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	string path = "Resource/XML/Idle.xml";
	document->LoadFile(path.c_str());

	XMLElement* textureAtlas = document->FirstChildElement();
	XMLElement* row = textureAtlas->FirstChildElement();

	vector<Action::Clip> clips;

	int w = 300;
	int h = 300;
	
	while (true)
	{
		if (row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();

		clips.emplace_back(x, y, w, h, srv);

		row = row->NextSiblingElement();
	}

	_action = make_shared<Action>(clips, "CUP_IDLE");
	_sprite = make_shared<Sprite>(srvPath, Vector2(w, h));
}
