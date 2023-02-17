#include "framework.h"
#include "SolarSystemScene.h"

SolarSystemScene::SolarSystemScene()
{
	_sun = make_shared<Planet>(L"Resource/Texture/Sun.png");
	_sun->SetPos(Vector2(CENTER_X, CENTER_Y));
	_sun->SetScale(Vector2(0.5f, 0.5f));

	_earth = make_shared<Planet>(L"Resource/Texture/earth.png");
	_earth->SetParent(_sun->GetVirtualTransform());
	_earth->GetVirtualTransform()->SetParent(_sun->GetVirtualTransform());
	_earth->SetScale(Vector2(0.5f, 0.5f));
	_earth->SetPos(Vector2(500, 0));

	_moon = make_shared<Planet>(L"Resource/Texture/moon.png");
	_moon->SetParent(_earth->GetVirtualTransform());
	_moon->SetScale(Vector2(0.5f, 0.5f));
	_moon->SetPos(Vector2(500, 0));
}

SolarSystemScene::~SolarSystemScene()
{
}

void SolarSystemScene::Init()
{
	_sun->SetPos(Vector2(CENTER_X, CENTER_Y));
}

void SolarSystemScene::Update()
{
	_sun->SetPos(MOUSE_POS);
	_sun->Update();
	_earth->Update();
	_moon->Update();
}

void SolarSystemScene::Render()
{
	_sun->Render();
	_earth->Render();
	_moon->Render();
}

void SolarSystemScene::PostRender()
{
	if (ImGui::Button("NextScene", { 100,100 }))
	{
		SCENE->SetScene("TutorialScene");
	}
}
