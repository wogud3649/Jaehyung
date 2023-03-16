#include "framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	_player = make_shared<Advanced_Player>();
	_player->GetFootCollider()->GetTransform()->SetPos(CENTER);
	_player->GetFootCollider()->GetTransform()->UpdateSRT();

	_brick = make_shared<Brick>();
	_brick->SetPlayer(_player);
	_brick->Load();
}

TestScene::~TestScene()
{
}

void TestScene::Init()
{
	CAMERA->SetTarget(_player->GetBodyCollider()->GetTransform());
	CAMERA->SetOffset(CENTER);
}

void TestScene::Fin()
{
	CAMERA->SetTarget(nullptr);
}

void TestScene::Update()
{
	_player->Update();
	_brick->Update();
}

void TestScene::Render()
{
	_player->Render();
}

void TestScene::PreRender()
{
	_brick->Render();
}

void TestScene::PostRender()
{
}
