#include "framework.h"
#include "BossScene.h"

BossScene::BossScene()
{
	_player = make_shared<Advanced_Player>();
	CAMERA->SetTarget(_player->GetBodyCollider()->GetTransform());
	
	_brick = make_shared<Brick>();
	_brick->SetPlayer(_player);
	_brick->Load();
	_player->GetFootCollider()->GetTransform()->SetPos(_brick->GetPlayerSpawn());

	_yggdrasil = make_shared<Yggdrasil>();
	_yggdrasil->SetTarget(_player);
	_yggdrasil->SetOriginPos(_brick->GetMonsterSpawn()[0]);

	CAMERA->SetOffset(CENTER);
}

BossScene::~BossScene()
{
}

void BossScene::Update()
{
	_player->Update();
	_yggdrasil->Update();
	_brick->Update();
}

void BossScene::Render()
{
	_player->Render();
}

void BossScene::PreRender()
{
	_brick->Render();
	_yggdrasil->Render();
}

void BossScene::PostRender()
{
	_yggdrasil->PostRender();
}
