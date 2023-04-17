#include "framework.h"
#include "UIScene.h"

UIScene::UIScene()
{
	_slider = make_shared<Slider>();
}

UIScene::~UIScene()
{
}

void UIScene::Init()
{
	UI->Init();
}

void UIScene::Fin()
{
}

void UIScene::Update()
{
	_slider->Update();
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
	_slider->PostRender();
}
