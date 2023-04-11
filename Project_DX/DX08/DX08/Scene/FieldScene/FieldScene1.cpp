#include "framework.h"
#include "FieldScene1.h"

FieldScene1::FieldScene1()
{
	_player = make_shared<Advanced_Player>();

	_brick = make_shared<Brick>();
	_brick->SetPlayer(_player);
}

FieldScene1::~FieldScene1()
{
}

void FieldScene1::Init()
{
	int randInt = rand() % 2;

	wstring filePath;
	switch (randInt)
	{
	case 0:
		filePath = L"Maps/Field1.map";
		break;
	case 1:
		filePath = L"Maps/Field2.map";
		break;
	default:
		break;
	}

	_brick->Load(filePath);
	_brick->SpawnMonster();

	CreateInteractObj();

	_player->GetFootCollider()->GetTransform()->SetPos(_brick->GetPlayerSpawn());

	CAMERA->SetTarget(_player->GetBodyCollider()->GetTransform());

	INVENTORY->SetPlayer(_player);

	SCENE->Init();

	_isClear = false;
}

void FieldScene1::Fin()
{
	SCENE->Fin();
}

void FieldScene1::Update()
{
	_player->Update();
	_brick->Update();

	INTERACTOBJ->GetDoor()->Update();
	if (_isClear)
		INTERACTOBJ->GetChest()->Update();

	SceneClear();
}

void FieldScene1::Render()
{
	_brick->Render();
	INTERACTOBJ->GetDoor()->Render();

	if (_isClear)
		INTERACTOBJ->GetChest()->Render();

	_player->Render();
}

void FieldScene1::PreRender()
{
}

void FieldScene1::PostRender()
{
	_player->PostRender();
	_brick->PostRender();
}

void FieldScene1::SceneClear()
{
	UINT activeMonsters = _brick->GetACtiveMonsters();
	if (activeMonsters == 0)
	{
		_isClear = true;
		INTERACTOBJ->GetChest()->Spawn();
	}
	else
	{
		_isClear = false;
		INTERACTOBJ->GetDoor()->DeActivate();
		INTERACTOBJ->GetChest()->Extinct();
	}
}

void FieldScene1::CreateInteractObj()
{
	Vector2 temp = _brick->GetDoorSpawn();
	INTERACTOBJ->CreateRandomDoor();
	INTERACTOBJ->GetDoor()->GetTransform()->SetPos(Vector2(temp.x, temp.y + 16));
	INTERACTOBJ->GetDoor()->Spawn();

	temp = _brick->GetChestSpawn();
	INTERACTOBJ->CreateRandomChest();
	INTERACTOBJ->GetChest()->GetTransform()->SetPos(Vector2(temp.x, temp.y + 16));
	INTERACTOBJ->SetPlayer(_player);
}
