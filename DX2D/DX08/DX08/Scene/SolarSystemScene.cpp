#include "framework.h"
#include "SolarSystemScene.h"

SolarSystemScene::SolarSystemScene()
{
	_sun = make_shared<Sun>();

	_earth = make_shared<Earth>();
	//_earth->GetTransform()->SetParent(_sun->GetTransform());
	//_earth->GetTransform()->GetScale() *= 0.3;
	//_earth->GetTransform()->GetPos().x += 150;

	_moon = make_shared<Quad>(L"Resource/Texture/Moon.png");
	//_moon->GetTransform()->SetParent(_earth->GetTransform());
	//_moon->GetTransform()->GetScale() *= 0.3;
	//_moon->GetTransform()->GetPos().x -= 100;
}

SolarSystemScene::~SolarSystemScene()
{
}

void SolarSystemScene::Update()
{
	_sun->Update();
	_earth->Update();
}

void SolarSystemScene::Render()
{
	_sun->Render();
	_earth->Render();
}
