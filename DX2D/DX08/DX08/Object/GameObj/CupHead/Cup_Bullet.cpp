#include "framework.h"
#include "Cup_Bullet.h"

Cup_Bullet::Cup_Bullet()
{
	Init();
}

Cup_Bullet::~Cup_Bullet()
{
}

void Cup_Bullet::Update()
{
	if (!_isActive)
		return;

	_sprite->Update();
	_action->Update();

	if (_duration <= 0)
		Reset();

	_duration -= DELTA_TIME;
	_sprite->GetTransform()->GetPos().x += _dir.x * _speed * DELTA_TIME;
}

void Cup_Bullet::Render()
{
	if (!_isActive)
		return;
	
	_sprite->SetActionClip(_action->GetCurClip());
	_sprite->Render();
}

void Cup_Bullet::SetDirection(int dir)
{
	if (dir == 0)
		_dir = { 1.0f,0.0f };
	else
		_dir = { -1.0f,0.0f };
	_sprite->GetTransform()->GetAngle() = _dir.Angle() - (PI / 2);
}

void Cup_Bullet::Init()
{
	CreateAction();

	_sprite->GetTransform()->GetScale() *= 0.25f;
}

void Cup_Bullet::CreateAction()
{
	wstring srvPath = L"Resource/Texture/Bullet/Special_Bullet_Loop.png";
	shared_ptr<SRV> srv = SRV_ADD(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	string path = "Resource/XML/Special_Bullet_Loop.xml";
	document->LoadFile(path.c_str());

	tinyxml2::XMLElement* textureAtlas = document->FirstChildElement();
	tinyxml2::XMLElement* row = textureAtlas->FirstChildElement();

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

	string actionName = "CUP_Bullet";
	_action = make_shared<Action>(clips, actionName);
	_sprite = make_shared<Sprite>(srvPath, Vector2(wAverage, hAverage));
}

void Cup_Bullet::Reset()
{
	_isActive = false;
	_duration = 2.0f;
	_action->Reset();
}
