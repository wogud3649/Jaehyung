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

	if (_lifeTime <= _delay)
		Reset();

	_delay += DELTA_TIME;
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

void Cup_Bullet::Enable()
{
	_isActive = true;
	_action->Play();
}

void Cup_Bullet::Init()
{
	CreateAction();
}

void Cup_Bullet::CreateAction()
{
	string xmlPath = "Resource/XML/Special_Bullet_Loop.xml";
	wstring srvPath = L"Resource/Texture/Bullet/Special_Bullet_Loop.png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "CUP_Bullet";
	_action = make_shared<Action>(xml.GetClips(), actionName, Action::Type::LOOP, 0.1f);
	Vector2 averageSize = xml.AverageSize() * 0.3f;
	_sprite = make_shared<Sprite>(srvPath, averageSize);
}

void Cup_Bullet::Reset()
{
	_isActive = false;
	_delay = 0.0f;
	_action->Reset();
}
