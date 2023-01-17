#include "framework.h"
#include "Bow.h"


Bow::Bow(wstring path)
{
	_quad = make_shared<Quad>(path);
	_virtual = make_shared<Transform>();
}

Bow::~Bow()
{
}

void Bow::Update()
{
	_quad->Update();
	_virtual->Update();
}

void Bow::Render()
{
	_quad->Render();
}

void Bow::SetPos(Vector2 pos)
{
	_quad->GetTransform()->GetPos() = pos;
	_virtual->GetPos() = pos;
}

void Bow::SetScale(Vector2 scale)
{
	_quad->GetTransform()->GetScale() = scale;
	_virtual->GetScale() = scale;
}

Vector2 Bow::GetPos()
{
	return Vector2(_quad->GetTransform()->GetPos());
}
