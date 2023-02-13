#include "framework.h"
#include "Cup_Monster.h"

Cup_Monster::Cup_Monster()
{
	CreatAction();
	Vector2 colliderSize = _sprite->GetClipSize();
	colliderSize.x *= 0.55f;
	colliderSize.y *= 0.85f;
	_col = make_shared<RectCollider>(colliderSize);

	_transform = _col->GetTransform();
	_sprite->GetTransform()->SetParent(_transform);
	_sprite->SetReverse();
	_action->Play();

	_muzzle = make_shared<Transform>();
	_muzzle->SetParent(_col->GetTransform());
	_muzzle->GetPos().y = 80.0f;

	for (int i = 0; i < _poolCount; i++)
		_bullets.emplace_back(make_shared<Cup_Monster_Bullet>());
}

Cup_Monster::~Cup_Monster()
{
	_transform = nullptr;
}

void Cup_Monster::Update()
{
	if (isAlive)
	{
		_col->Update();
	
		_muzzle->Update();
	}
	else
	{
		Death();
		Revive();
	}
	if (_sprite->GetFilter()->_data.value1 > 0)
	{
		_sprite->Update();
		_action->Update();
	}

	for (auto bullet : _bullets)
		bullet->Update();
}

void Cup_Monster::Render()
{
	if (isAlive)
	{
		_col->Render();
		_sprite->SetActionClip(_action->GetCurClip());
	}
	if (_sprite->GetFilter()->_data.value1 > 0)
		_sprite->Render();


	for (auto bullet : _bullets)
		bullet->Render();
}

void Cup_Monster::EnAble()
{
	_sprite->GetFilter()->_data.selected = 0;
	_sprite->GetFilter()->_data.value1 = 500;
	_action->Play();
	_curHp = _maxHp;
	isAlive = true;
	_col->isActive = true;
}

void Cup_Monster::DisAble()
{
	_action->Reset();
	_col->isActive = false;
	isAlive = false;
}

void Cup_Monster::Fire()
{
	shared_ptr<Cup_Monster_Bullet> bullet = SelectBullet();

	bullet->SetPostion(_muzzle->GetWorldPos());
	bullet->Fire();
}

void Cup_Monster::Damaged()
{
	_curHp -= 1;
	if (_curHp <= 0)
	{
		DisAble();
	}
}

void Cup_Monster::Revive()
{
	if (KEY_DOWN(VK_F2))
	{
		EnAble();
	}
}

void Cup_Monster::Death()
{
	if (_sprite->GetFilter()->_data.selected != 1)
		_sprite->GetFilter()->_data.selected = 1;
	if (_sprite->GetFilter()->_data.value1 >= 0)
		_sprite->GetFilter()->_data.value1 -= 500 * DELTA_TIME;
}

void Cup_Monster::SetTarget(shared_ptr<Cup_Advanced_Player> target)
{
	_target = target;
	for (auto bullet : _bullets)
		bullet->SetTarget(target);
}

void Cup_Monster::CreatAction()
{
	wstring srvPath = L"Resource/Texture/CupHead/Clown_Page_Last_Spawn_Penguin_Start.png";
	string xmlPath = "Resource/XML/Clown_Page_Last_Spawn_Penguin_Start.xml";
	MyXML xml = MyXML(xmlPath, srvPath);

	_action = make_shared<Action>(xml.GetClips(), "Boss_IDLE", Action::Type::PINGPONG, 0.05f);
	Vector2 size = xml.AverageSize() * 0.7f;
	_sprite = make_shared<FilterSprite>(srvPath, size);

	_action->SetCallBack(std::bind(&Cup_Monster::Fire, this));
}

shared_ptr<Cup_Monster_Bullet> Cup_Monster::SelectBullet()
{
	for (auto bullet : _bullets)
	{
		if (bullet->isActive == false)
		{
			return bullet;
		}
	}
}