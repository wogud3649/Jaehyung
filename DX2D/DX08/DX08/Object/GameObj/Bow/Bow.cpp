#include "framework.h"
#include "Bow.h"


Bow::Bow(wstring path)
{
	_quad = make_shared<Quad>(path);

	for (int i = 0; i < _virtualSize; i++)
	{
		_virtuals.push_back(make_shared<Transform>());
	}
}

Bow::~Bow()
{
}

void Bow::Update()
{
	_quad->Update();

	for (int i = 0; i < _virtualSize; i++)
	{
		_virtuals[i]->Update();
	}
}

void Bow::Render()
{
	_quad->Render();
}

void Bow::SetPos(Vector2 pos)
{
	_quad->GetTransform()->GetPos() = pos;
	for (int i = 0; i < _virtualSize; i++)
	{
		_virtuals[i]->GetPos() = pos;
	}
}

void Bow::SetScale(Vector2 scale)
{
	_quad->GetTransform()->GetScale() = scale;
	for (int i = 0; i < _virtualSize; i++)
	{
		_virtuals[i]->GetScale() = scale;
	}
}