#include "framework.h"
#include "Cup_Monster_Bullet.h"

Cup_Monster_Bullet::Cup_Monster_Bullet()
{
	CreateAction();

	_col = make_shared<CircleCollider>(23.0f);
	_col->GetTransform()->SetParent(_sprite->GetTransform());
	_col->GetTransform()->GetPos().y += 40.0f;
}

Cup_Monster_Bullet::~Cup_Monster_Bullet()
{
}

void Cup_Monster_Bullet::Update()
{
	if (!isActive) return;

	_col->Update();

	_delay += DELTA_TIME;

	if (_delay >= _lifeTime)
	{
		_action->Reset();
		isActive = false;
		_delay = 0.0f;
	}

	_sprite->GetTransform()->GetPos() += _direction * _speed * DELTA_TIME;

	_action->Update();
	_sprite->Update();

	if (_target.expired() == false)
	{
		if (_target.lock()->GetBodyCollider()->isActive == false)
			return;
		if (_col->IsCollision(_target.lock()->GetBodyCollider()))
		{
			_target.lock()->Damaged();
			_action->Reset();
			isActive = false;
			_delay = 0.0f;
		}
	}
}

void Cup_Monster_Bullet::Render()
{
	if (!isActive) return;

	_col->Render();

	_sprite->SetActionClip(_action->GetCurClip());
	_sprite->Render();
}

void Cup_Monster_Bullet::Fire(Vector2 dir)
{
	_action->Play();
	_sprite->GetTransform()->GetAngle() = dir.Angle() - PI * 0.5f;
	_direction = dir.NormalVector2();
}

void Cup_Monster_Bullet::CreateAction()
{
	string xmlPath = "Resource/XML/Special_Bullet_Loop.xml";
	wstring srvPath = L"Resource/Texture/CupHead/Special_Bullet_Loop.png";

	MyXML xml = MyXML(xmlPath, srvPath);

	_action = make_shared<Action>(xml.GetClips(), "Bullet");
	Vector2 averageSize = xml.AverageSize() * 0.3f;
	_sprite = make_shared<Sprite>(srvPath, averageSize);
}
