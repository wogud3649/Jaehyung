#include "framework.h"
#include "CupHeadScene.h"

CupHeadScene::CupHeadScene()
{
	_player = make_shared<Cup_Advanced_Player>();
	_player->GetTransform()->GetPos() = CENTER;

	_bg = make_shared<Cup_Bg>();
	_bg->SetPos(CENTER);
	_bg->Update();

	_player->GetTransform()->GetPos().y -= 170.0f;
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Update()
{
	_player->Update();
}

void CupHeadScene::Render()
{
	_player->Render();
}

void CupHeadScene::PreRender()
{
	_bg->Render();
}
