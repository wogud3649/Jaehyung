#include "framework.h"
#include "BossScene.h"

BossScene::BossScene()
{
	_player = make_shared<Advanced_Player>();
	CAMERA->SetTarget(_player->GetBodyCollider()->GetTransform());
	
	_brick = make_shared<Brick>();
	_brick->Load();

	CAMERA->SetOffset(CENTER);
}

BossScene::~BossScene()
{
}

void BossScene::Update()
{
	_player->Update();
	_brick->Update();
}

void BossScene::Render()
{
	_player->Render();
}

void BossScene::PreRender()
{
	_brick->Render();
}
