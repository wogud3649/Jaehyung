#include "framework.h"
#include "Earth.h"

Earth::Earth()
{
	_earth = make_shared<Quad>(L"Resource/Texture/Earth.png");
}

Earth::~Earth()
{
}

void Earth::Update()
{
	_earth->GetTransform()->GetAngle() += 0.0001;
	_earth->Update();
}

void Earth::Render()
{
	_earth->Render();
}

shared_ptr<Transform> Earth::GetTransform()
{
	return _earth->GetTransform();
}
