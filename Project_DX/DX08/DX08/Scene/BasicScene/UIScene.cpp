#include "framework.h"
#include "UIScene.h"

UIScene::UIScene()
{
	_circle = make_shared<CircleCollider>(20);
}

UIScene::~UIScene()
{
}

void UIScene::Update()
{
	_circle->Update();
}

void UIScene::Render()
{
	_circle->Render();
}
