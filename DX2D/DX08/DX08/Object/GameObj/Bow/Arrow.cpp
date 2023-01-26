#include "framework.h"
#include "Arrow.h"

Arrow::Arrow()
{
	_quad = make_shared<Quad>(L"Resource/Texture/Bullet.png");
	_quad->GetTransform()->SetScale(Vector2(0.2f, 0.2f));

	_col = make_shared<CircleCollider>(50);
	_col->GetTransform()->SetParent(_quad->GetTransform());
	_col->GetTransform()->GetPos().x += 150;
}

Arrow::~Arrow()
{
}

void Arrow::Update()
{
	if (_isActive == false)
		return;
	if (_duration > 5.0)
	{
		_isActive = false;
		_duration = 0.0;
	}

	_quad->GetTransform()->Move(_dir * _speed * DELTA_TIME);
	_duration += DELTA_TIME;

	_quad->Update();
	_col->Update();
}

void Arrow::Render()
{
	if (_isActive == false)
		return;

	_quad->Render();
	//_col->Render();
}

void Arrow::SetDirection(Vector2 dir)
{
	dir.Normalize();
	_dir = dir;
}
