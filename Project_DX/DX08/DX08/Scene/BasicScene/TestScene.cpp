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
	if (_filePath == L"")
		_filePath = L"Maps/Field1.map";

	wstring filePath = _filePath;

	_brick->Load(filePath);
	_brick->SpawnMonster();
	_brick->Update();

	_player->GetFootCollider()->GetTransform()->SetPos(_brick->GetPlayerSpawn());

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
