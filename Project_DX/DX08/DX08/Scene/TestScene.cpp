#include "framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	_player = make_shared<Player>();
	_player->GetTransform()->SetPos(CENTER);
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	_player->Update();
}

void TestScene::Render()
{
	_player->Render();
}
