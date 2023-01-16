#include "framework.h"
#include "Sun.h"

Sun::Sun()
{
	_sun = make_shared<Quad>(L"Resource/Texture/Sun.png");
	_sun->GetTransform()->GetPos() = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f };
	_sun->GetTransform()->GetScale() *= 2;

	_earth = make_shared<Earth>();
	_earth->GetTransform()->SetParent(_sun->GetTransform());
	_earth->GetTransform()->GetPos().x += 120;
	_earth->GetTransform()->GetScale() *= 0.3;
}

Sun::~Sun()
{
}

void Sun::Update()
{
	_sun->GetTransform()->GetAngle() += 0.0001;
	_sun->Update();
	_earth->Update();
}

void Sun::Render()
{
	_sun->Render();
	_earth->Render();
}

shared_ptr<Transform> Sun::GetTransform()
{
	return _sun->GetTransform();
}
