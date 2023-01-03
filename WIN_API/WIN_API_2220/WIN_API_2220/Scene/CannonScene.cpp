#include "framework.h"
#include "CannonScene.h"

CannonScene::CannonScene()
{
	_cannon = make_shared<Cannon>();
}

CannonScene::~CannonScene()
{
}

void CannonScene::Update()
{
	_cannon->Update();
}

void CannonScene::Render(HDC hdc)
{
	_cannon->Render(hdc);
}
