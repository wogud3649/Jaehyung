#include "framework.h"
#include "Earth.h"

Earth::Earth()
{
	_earth = make_shared<Quad>(L"Resource/Texture/Earth.png");
	_moon = make_shared<Moon>();
	_moon->GetTransform()->SetParent(_earth->GetTransform());
	_moon->GetTransform()->GetPos().x += 100;
	_moon->GetTransform()->GetScale() *= 0.3;
}

Earth::~Earth()
{
}

void Earth::Update()
{
	_earth->GetTransform()->GetAngle() += 0.0001;
	_earth->Update();
	_moon->Update();
}

void Earth::Render()
{
	_earth->Render();
	_moon->Render();
}

shared_ptr<Transform> Earth::GetTransform()
{
	return _earth->GetTransform();
}
