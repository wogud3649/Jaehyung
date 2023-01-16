#include "framework.h"
#include "SolarSystemScene.h"

SolarSystemScene::SolarSystemScene()
{
	_sun = make_shared<Planet>(L"Resource/Texture/Sun.png");
	_sun->SetPos(Vector2(CENTER_X, CENTER_Y));
	_sun->SetScale(Vector2(2.0f, 2.0f));

	_earth = make_shared<Planet>(L"Resource/Texture/Earth.png");
	_earth->SetParent(_sun->GetVirtualTransform());
	_earth->SetScale(Vector2(0.5f, 0.5f));
	_earth->SetPos(Vector2(150, 0));
}

SolarSystemScene::~SolarSystemScene()
{
}

void SolarSystemScene::Update()
{
	_sun->SetPos(mousePos);
	_sun->Update();
	_earth->Update();
}

void SolarSystemScene::Render()
{
	_sun->Render();
	_earth->Render();
}
