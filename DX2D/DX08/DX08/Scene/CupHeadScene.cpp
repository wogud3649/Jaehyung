#include "framework.h"
#include "CupHeadScene.h"

CupHeadScene::CupHeadScene()
{
	_player = make_shared<Cup_Advanced_Player>();
	_player->GetBodyCollider()->GetTransform()->GetPos() = CENTER;
	_monster = make_shared<Cup_Monster>();
	_monster->GetTransform()->GetPos() = Vector2(WIN_WIDTH - 300.0f, CENTER.y);
	_monster->SetTarget(_player);
	_player->SetTarget(_monster);

	_bg = make_shared<Cup_Bg>();
	_bg->SetPos(CENTER);
	_bg->SetPlayer(_player);

	Audio::GetInstance()->Add("bgm", "Resource/Sound/BGM.mp3", true);
	Audio::GetInstance()->Add("jump", "Resource/Sound/jump.wav");
	Audio::GetInstance()->Play("bgm");
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Update()
{
	_bg->Update();
	_player->Update();
	_monster->Update();
}

void CupHeadScene::PreRender()
{
	_bg->Render();
}

void CupHeadScene::Render()
{
	_monster->Render();
	_player->Render();
}

void CupHeadScene::PostRender()
{
	ImGui::SliderInt("Player HP", &_player->GetHp(), 0, 3);
	ImGui::SliderInt("Monster HP", &_monster->GetHp(), 0, 10);
	ImGui::SliderInt("Selected", &_monster->GetSprite()->GetFilter()->_data.selected, 0, 1);
	ImGui::SliderInt("Mosaic", &_monster->GetSprite()->GetFilter()->_data.value1, 0, 3000);
}
