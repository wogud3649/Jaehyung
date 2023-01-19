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

void BowScene::PostRender()
{
	ImGui::SliderFloat("BowX", &_bow->GetTransform()->GetPos().x, 0, WIN_WIDTH);
	ImGui::SliderFloat("BowY", &_bow->GetTransform()->GetPos().y, 0, WIN_HEIGHT);
}
