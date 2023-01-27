#include "framework.h"
#include "Bow_Arrow.h"

Bow_Arrow::Bow_Arrow()
{
	_quad = make_shared<Quad>(L"Resource/Texture/Bullet.png");
	_quad->GetTransform()->SetScale(Vector2(0.2f, 0.2f));

	_col = make_shared<CircleCollider>(50);
	_col->GetTransform()->SetParent(_quad->GetTransform());
	_col->GetTransform()->GetPos().x += 150;
}

Bow_Arrow::~Bow_Arrow()
{
}

void Bow_Arrow::Update()
{
	if (_isActive == false)
		return;
	
	_duration += DELTA_TIME;

	if (_duration > 2.5f)
	{
		DisAble();
	}

	_quad->GetTransform()->Move(_dir * _speed * DELTA_TIME);

	_quad->Update();
	_col->Update();

	if (!_target.expired())
	{
		if (_col->IsCollision(_target.lock()->GetCollider()))
		{
			if (_target.lock()->GetCollider()->isActive)
			{
				_target.lock()->Damaged(_damage);
				DisAble();
			}
		}
	}

}

void Bow_Arrow::Render()
{
	if (_isActive == false)
		return;

	_quad->Render();
	_col->Render();
}

void Bow_Arrow::SetDirection(Vector2 dir)
{
	dir.Normalize();
	_dir = dir;
}

void Bow_Arrow::EnAble()
{
	_isActive = true;
	_col->isActive = true;
}

void Bow_Arrow::DisAble()
{
	_isActive = false;
	_col->isActive = false;
	_duration = 0.0f;
}
