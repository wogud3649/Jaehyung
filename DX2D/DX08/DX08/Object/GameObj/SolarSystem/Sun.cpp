#include "framework.h"
#include "Sun.h"

Sun::Sun()
{
	_sun = make_shared<Quad>(L"Resource/Texture/Sun.png");
}

Sun::~Sun()
{
}

void Sun::Update()
{
	_sun->GetTransform()->GetAngle() += 0.0001;
	_sun->Update();
}

void Sun::Render()
{
	_sun->Render();
}

shared_ptr<Transform> Sun::GetTransform()
{
	return _sun->GetTransform();
}
