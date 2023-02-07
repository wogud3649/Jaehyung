#include "framework.h"
#include "CupHeadScene.h"

CupHeadScene::CupHeadScene()
{
	_player = make_shared<Cup_Advanced_Player>();
	_player->GetCollider()->GetTransform()->GetPos() = CENTER;

	_bg = make_shared<Cup_Bg>();
	_bg->SetPos(CENTER);

	_player->GetCollider()->GetTransform()->GetPos().y -= 180.0f;
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Update()
{
	_bg->Update();
	_player->Update();

	_bg->GetCollider()->Block(dynamic_pointer_cast<CircleCollider>(_player->GetCollider()));
}

void CupHeadScene::PreRender()
{
	_bg->Render();
}

void CupHeadScene::Render()
{
	_player->Render();
}
