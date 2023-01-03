#include "framework.h"
#include "ArkanoidScene.h"

ArkanoidScene::ArkanoidScene()
{
	_arkanoid = make_shared<Arkanoid>();
}

ArkanoidScene::~ArkanoidScene()
{
}

void ArkanoidScene::Update()
{
	_arkanoid->Update();
}

void ArkanoidScene::Render(HDC hdc)
{
	_arkanoid->Render(hdc);
}