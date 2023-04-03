#include "framework.h"
#include "UIScene.h"

UIScene::UIScene()
{

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
	INVENTORY->Update();
	UI->Update();
}

void UIScene::Render()
{
}

void UIScene::PostRender()
{
	INVENTORY->PostRender();
	UI->PostRender();
}
