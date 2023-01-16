#include "framework.h"
#include "SolarSystemScene.h"

SolarSystemScene::SolarSystemScene()
{
	_sun = make_shared<Sun>();
	_sun->GetTransform()->GetPos() = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f };
	_sun->GetTransform()->GetScale() *= 2;
	_sunTrans = make_shared<Transform>();
	_sunTrans->GetPos() = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f };
	_sunTrans->GetScale() *= 2;

	_earth = make_shared<Earth>();
	_earth->GetTransform()->SetParent(_sunTrans);
	_earth->GetTransform()->GetScale() *= 0.3;
	_earth->GetTransform()->GetPos().x += 150;
	_earthTrans = make_shared<Transform>();
	_earthTrans->SetParent(_sunTrans);
	_earthTrans->GetScale() *= 0.3;
	_earthTrans->GetPos().x += 150;
	
	_moon = make_shared<Moon>();
	_moon->GetTransform()->SetParent(_earthTrans);
	_moon->GetTransform()->GetScale() *= 0.3;
	_moon->GetTransform()->GetPos().x -= 100;
}

SolarSystemScene::~SolarSystemScene()
{
}

void SolarSystemScene::Update()
{
	_sunTrans->GetAngle() += 0.0002;
	_earthTrans->GetAngle() += 0.0006;

	_sun->Update();
	_sunTrans->Update();
	_earth->Update();
	_earthTrans->Update();
	_moon->Update();
}

void SolarSystemScene::Render()
{
	_sun->Render();
	_earth->Render();
	_moon->Render();
}
