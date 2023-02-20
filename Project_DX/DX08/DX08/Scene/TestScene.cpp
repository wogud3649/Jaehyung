#include "framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	_player = make_shared<Advanced_Player>();
	_player->GetBodyCollider()->GetTransform()->SetPos(CENTER);

	_background = make_shared<Background>();
	_background->GetTransform()->SetPos(CENTER);
	_background->SetPlayer(_player);
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	_background->Update();
	_player->Update();
}

void TestScene::Render()
{
	_player->Render();
}

void TestScene::PreRender()
{
	_background->Render();
}

void TestScene::PostRender()
{
}
