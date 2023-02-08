#include "framework.h"
#include "CupHeadScene.h"

CupHeadScene::CupHeadScene()
{
	_player = make_shared<Cup_Advanced_Player>();
	_player->GetBodyCollider()->GetTransform()->GetPos() = CENTER;

	_bg = make_shared<Cup_Bg>();
	_bg->SetPos(CENTER);
	_bg->SetPlayer(_player);

	_player->GetTransform()->GetPos().y -= 180.0f;
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Update()
{
	_bg->Update();
	_player->Update();
}

void CupHeadScene::PreRender()
{
	_bg->Render();
}

void CupHeadScene::Render()
{
	_player->Render();
}
