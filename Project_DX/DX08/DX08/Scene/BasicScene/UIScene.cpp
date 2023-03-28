#include "framework.h"
#include "UIScene.h"

UIScene::UIScene()
{
	_pannel = make_shared<Quad>(L"Resources/Texture/UI/InventoryPannel.png");
	_pannel->GetTransform()->SetPos(CENTER);
}

UIScene::~UIScene()
{
}

void UIScene::Update()
{
	_pannel->Update();
}

void UIScene::Render()
{
	_pannel->Render();
}
