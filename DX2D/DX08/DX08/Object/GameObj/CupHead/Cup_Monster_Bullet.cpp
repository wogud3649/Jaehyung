#include "framework.h"
#include "Cup_Monster_Bullet.h"

Cup_Monster_Bullet::Cup_Monster_Bullet()
{
	CreateAction();

	_col = make_shared<CircleCollider>(23.0f);
	_col->GetTransform()->SetParent(_sprite->GetTransform());
	_col->GetTransform()->GetPos().y += 40.0f;

	wstring file = L"Resource/Texture/Effects/hit_4x2.png";
	_effect = make_shared<Effect>(file, Vector2(4, 2), Vector2(200, 200), 0.05f);
	EFFECT->AddEffect(file, Vector2(4, 2), Vector2(200, 200), 0.05f);

	file = L"Resource/Texture/Effects/smoke_4x4.png";
	_effect = make_shared<Effect>(file, Vector2(4, 4), Vector2(200, 200), 0.02f);
	EFFECT->AddEffect(file, Vector2(4, 4), Vector2(200, 200), 0.05f);
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
			Camera::GetInstance()->ShakeStart(10.0f, 0.3f);
			EFFECT->Play("hit_4x2", _col->GetTransform()->GetWorldPos());
			_target.lock()->Damaged(10.0f);
			DisAble();
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

void Cup_Monster_Bullet::EnAble()
{
	_action->Play();
	isActive = true;
	_col->isActive = true;
}

void Cup_Monster_Bullet::DisAble()
{
	_action->Reset();
	isActive = false;
	_col->isActive = false;
	_delay = 0.0f;
}

void Cup_Monster_Bullet::Fire()
{
	EnAble();
	_direction = (_target.lock()->GetBodyCollider()->GetTransform()->GetWorldPos() - _col->GetTransform()->GetWorldPos()).NormalVector2();
	_sprite->GetTransform()->GetAngle() = _direction.Angle() - PI * 0.5f;
	EFFECT->Play("smoke_4x4", _col->GetTransform()->GetWorldPos());
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
