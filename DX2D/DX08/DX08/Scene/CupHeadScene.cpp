#include "framework.h"
#include "CupHeadScene.h"

CupHeadScene::CupHeadScene()
{
	_player = make_shared<Cup_Advanced_Player>();
	_player->GetTransform()->GetPos() = CENTER;

	_bg = make_shared<Cup_Bg>();
	_bg->SetPos(CENTER);

	_player->GetTransform()->GetPos().y -= 170.0f;
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Update()
{
	_player->Update();
	_bg->Update();

	//_bg->GetCollider()->Block(_player->GetCollider());
}

void CupHeadScene::Render()
{
	_player->Render();
}

void CupHeadScene::PreRender()
{
	_bg->Render();
}
