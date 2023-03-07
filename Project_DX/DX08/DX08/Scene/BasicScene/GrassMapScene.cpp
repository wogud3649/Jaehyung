#include "framework.h"
#include "GrassMapScene.h"

GrassMapScene::GrassMapScene()
{
	_player = make_shared<Advanced_Player>();
	_player->GetFootCollider()->GetTransform()->SetPos(CENTER);

	_brick = make_shared<Brick>();
	_brick->Load();
}

GrassMapScene::~GrassMapScene()
{
}

void GrassMapScene::Update()
{
	_brick->Update();
	_player->Update();
}

void GrassMapScene::Render()
{
	_brick->Render();
	_player->Render();
}
