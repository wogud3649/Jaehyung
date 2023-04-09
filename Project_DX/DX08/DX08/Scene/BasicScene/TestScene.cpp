#include "framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	_player = make_shared<Advanced_Player>();

	INVENTORY->SetPlayer(_player);

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
	Vector2 temp = _brick->GetDoorSpawn();
	INTERACTOBJ->CreateRandomDoor();
	INTERACTOBJ->GetDoor()->GetTransform()->SetPos(Vector2(temp.x, temp.y + 16));

	temp = _brick->GetChestSpawn();
	INTERACTOBJ->CreateRandomChest();
	INTERACTOBJ->GetChest()->GetTransform()->SetPos(Vector2(temp.x, temp.y + 16));
	_brick->Update();
	INTERACTOBJ->SetPlayer(_player);

	_player->GetFootCollider()->GetTransform()->SetPos(_brick->GetPlayerSpawn());

	CAMERA->SetTarget(_player->GetBodyCollider()->GetTransform());
	CAMERA->SetOffset(CENTER);

	UI->Init();
}

void TestScene::Fin()
{
	CAMERA->SetTarget(nullptr);
}

void TestScene::Update()
{
	INVENTORY->Update();
	UI->Update();
	if (INVENTORY->IsOpen())
		return;
	_player->Update();
	_brick->Update();
	INTERACTOBJ->GetDoor()->Update();
	INTERACTOBJ->GetChest()->Update();
}

void TestScene::Render()
{
	INTERACTOBJ->GetDoor()->Render();
	INTERACTOBJ->GetChest()->Render();
	_player->Render();
}

void TestScene::PreRender()
{
	_brick->Render();
}

void TestScene::PostRender()
{
	INVENTORY->PostRender();
	UI->PostRender();
	_player->PostRender();
	_brick->PostRender();
}
