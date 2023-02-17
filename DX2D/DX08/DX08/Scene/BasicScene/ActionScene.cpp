#include "framework.h"
#include "ActionScene.h"

ActionScene::ActionScene()
{
	_zelda = make_shared<Zelda>();
	_zelda->SetPos(CENTER);
}

ActionScene::~ActionScene()
{
}

void ActionScene::Update()
{
	_zelda->Update();
}

void ActionScene::Render()
{
	_zelda->Render();
}

void ActionScene::PostRender()
{
}
