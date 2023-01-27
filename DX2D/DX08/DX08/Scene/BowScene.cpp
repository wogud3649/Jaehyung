#include "framework.h"
#include "BowScene.h"

BowScene::BowScene()
{
	_monster = make_shared<Bow_Monster>();

	_bow = make_shared<Bow>();
	_bow->SetTarget(_monster);
}

BowScene::~BowScene()
{
}

void BowScene::Update()
{
	if (KEY_DOWN(VK_F2))
	{
		_monster->Revive();
	}

	_bow->Update();
	_monster->Update();
}

void BowScene::Render()
{
	_bow->Render();
	_monster->Render();
}

void BowScene::PostRender()
{
	ImGui::SliderFloat("BowX", &_bow->GetTransform()->GetPos().x, 0, WIN_WIDTH);
	ImGui::SliderFloat("BowY", &_bow->GetTransform()->GetPos().y, 0, WIN_HEIGHT);
	
	ImGui::SliderInt("Monster HP", &_monster->GetHp(), 0, 100);
}
