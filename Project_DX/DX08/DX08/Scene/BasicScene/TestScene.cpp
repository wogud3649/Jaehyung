#include "framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	_player = make_shared<Advanced_Player>();

	_brick = make_shared<Brick>();
	_brick->SetPlayer(_player);
}

TestScene::~TestScene()
{
}

void TestScene::Init()
{
	wstring filePath = _filePath;
	if (_filePath == L"")
		return;
	_brick->Load(filePath);

	_player->GetFootCollider()->GetTransform()->SetPos(CENTER);
	_player->GetFootCollider()->GetTransform()->UpdateSRT();

	CAMERA->SetTarget(_player->GetBodyCollider()->GetTransform());
	CAMERA->SetOffset(CENTER);
}

void TestScene::Fin()
{
	CAMERA->SetTarget(nullptr);
}

void TestScene::Update()
{
	if (_filePath == L"")
		return;

	_player->Update();
	_brick->Update();
}

void TestScene::Render()
{
	if (_filePath == L"")
		return;

	_player->Render();
}

void TestScene::PreRender()
{
	if (_filePath == L"")
		return;

	_brick->Render();
}

void TestScene::PostRender()
{
}
