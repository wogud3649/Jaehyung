#include "framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	_player = make_shared<Advanced_Player>();
	_player->GetFootCollider()->GetTransform()->SetPos(CENTER);
	_player->GetFootCollider()->GetTransform()->UpdateSRT();

	_background = make_shared<Background>();
	_background->GetTransform()->SetPos(CENTER);
	_background->SetPlayer(_player);

	CAMERA->SetTarget(_player->GetBodyCollider()->GetTransform());
	CAMERA->SetLeftBottom(_background->LeftBottom());
	CAMERA->SetRightTop(_background->RightTop());
	CAMERA->SetOffset(CENTER);
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
