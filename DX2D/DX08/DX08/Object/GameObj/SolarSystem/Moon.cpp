#include "framework.h"
#include "Moon.h"

Moon::Moon()
{
	_moon = make_shared<Quad>(L"Resource/Texture/Moon.png");
}

Moon::~Moon()
{
}

void Moon::Update()
{
	_moon->GetTransform()->GetAngle() += 0.0001;
	_moon->Update();
}

void Moon::Render()
{
	_moon->Render();
}

shared_ptr<Transform> Moon::GetTransform()
{
	return _moon->GetTransform();
}
