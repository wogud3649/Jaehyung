#include "framework.h"
#include "UIScene.h"

UIScene::UIScene()
{
	_inventory = make_shared<Inventory>();
}

UIScene::~UIScene()
{
}

void UIScene::Init()
{
}

void UIScene::Fin()
{
}

void UIScene::Update()
{
	_inventory->Update();
}

void UIScene::Render()
{
}

void UIScene::PostRender()
{
	_inventory->PostRender();
}
