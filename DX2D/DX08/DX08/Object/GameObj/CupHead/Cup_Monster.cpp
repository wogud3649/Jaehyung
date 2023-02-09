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
	_col->Update();
	
	_action->Update();
	_sprite->Update();
	_muzzle->Update();
	for (auto bullet : _bullets)
		bullet->Update();

	_shootTime += DELTA_TIME;
	if (_shootTime >= _shootDelay)
	{
		_shootTime = 0.0f;
		Fire();
	}
}

void Cup_Monster::Render()
{
	_col->Render();
	_sprite->SetActionClip(_action->GetCurClip());
	_sprite->Render();
	for (auto bullet : _bullets)
		bullet->Render();
}

void Cup_Monster::Fire()
{
	shared_ptr<Cup_Monster_Bullet> bullet = SelectBullet();
	Vector2 dir = _player.lock()->GetTransform()->GetPos() - _muzzle->GetWorldPos();

	bullet->SetPostion(_muzzle->GetWorldPos());
	bullet->isActive = true;
	bullet->Fire(dir);
}

void Cup_Monster::SetPlayer(shared_ptr<Cup_Advanced_Player> player)
{
	_player = player;
	for (auto bullet : _bullets)
		bullet->SetTarget(player);
}

void Cup_Monster::CreatAction()
{
	wstring srvPath = L"Resource/Texture/CupHead/Clown_Page_Last_Spawn_Penguin_Start.png";
	string xmlPath = "Resource/XML/Clown_Page_Last_Spawn_Penguin_Start.xml";
	MyXML xml = MyXML(xmlPath, srvPath);

	_action = make_shared<Action>(xml.GetClips(), "Boss_IDLE", Action::Type::PINGPONG);
	Vector2 size = xml.AverageSize() * 0.7f;
	_sprite = make_shared<Sprite>(srvPath, size);
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