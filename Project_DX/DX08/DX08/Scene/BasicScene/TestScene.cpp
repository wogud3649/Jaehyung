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

	CreateInteractObj();

	_player->GetFootCollider()->GetTransform()->SetPos(_brick->GetPlayerSpawn());

	CAMERA->SetTarget(_player->GetBodyCollider()->GetTransform());

	INVENTORY->SetPlayer(_player);

	SCENE->Init();

	_isClear = false;
}

void TestScene::Fin()
{
	SCENE->Fin();
}

void TestScene::Update()
{
	INTERACTOBJ->GetDoor()->Update();
	if (_isClear)
		INTERACTOBJ->GetChest()->Update();

	_player->Update();
	_brick->Update();

	SceneClear();
}

void TestScene::Render()
{
	_brick->Render();

	INTERACTOBJ->GetDoor()->Render();
	if (_isClear)
		INTERACTOBJ->GetChest()->Render();

	_player->Render();
}

void TestScene::PreRender()
{
}

void TestScene::PostRender()
{
	_player->PostRender();
	_brick->PostRender();
}

void TestScene::SceneClear()
{
	if (_isClear)
		return;

	UINT activeMonsters = _brick->GetACtiveMonsters();
	if (activeMonsters == 0)
	{
		_isClear = true;
		INTERACTOBJ->GetChest()->Spawn();
	}
}

void TestScene::CreateInteractObj()
{
	Vector2 temp = _brick->GetDoorSpawn();
	INTERACTOBJ->GetDoor()->GetTransform()->SetPos(Vector2(temp.x, temp.y + 16));
	INTERACTOBJ->GetDoor()->DeActivate();
	INTERACTOBJ->GetDoor()->SetRandom();
	INTERACTOBJ->GetDoor()->Spawn();

	temp = _brick->GetChestSpawn();
	INTERACTOBJ->GetChest()->GetTransform()->SetPos(Vector2(temp.x, temp.y + 16));
	INTERACTOBJ->GetChest()->Extinct();
	INTERACTOBJ->GetChest()->SetRandom();
	INTERACTOBJ->SetPlayer(_player);
}