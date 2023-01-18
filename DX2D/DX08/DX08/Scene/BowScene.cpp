#include "framework.h"
#include "BowScene.h"

BowScene::BowScene()
{
	_bow = make_shared<Bow>();
}

BowScene::~BowScene()
{
}

void BowScene::Update()
{
	_bow->Update();
}

void BowScene::Render()
{
	_bow->Render();
}
