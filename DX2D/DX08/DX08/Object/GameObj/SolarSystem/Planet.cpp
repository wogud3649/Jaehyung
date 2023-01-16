#include "framework.h"
#include "Planet.h"


Planet::Planet(wstring path)
{
	_quad = make_shared<Quad>(path);

	_virtualTrans = make_shared<Transform>();
}

Planet::~Planet()
{
}

void Planet::Update()
{
	_quad->GetTransform()->GetAngle() += _speed;

	_virtualTrans->GetAngle() += _speed * 2;

	_quad->Update();
	_virtualTrans->Update();
}

void Planet::Render()
{
	_quad->Render();
}

void Planet::SetPos(Vector2 pos)
{
	_quad->GetTransform()->GetPos() = pos;
	_virtualTrans->GetPos() = pos;
}

void Planet::SetScale(Vector2 scale)
{
	_quad->GetTransform()->GetScale() = scale;
	_virtualTrans->GetScale() = scale;
}
