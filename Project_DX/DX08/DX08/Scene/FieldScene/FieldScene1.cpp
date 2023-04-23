#include "framework.h"
#include "FieldScene1.h"

FieldScene1::FieldScene1()
{
	_brick = make_shared<Brick>();
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
	_brick->Update();

	CreateInteractObj();

	PLAYER->GetFootCollider()->GetTransform()->SetPos(_brick->GetPlayerSpawn());

	CAMERA->SetTarget(PLAYER->GetBodyCollider()->GetTransform());

	SCENE->Init();

	_isClear = false;
}

void FieldScene1::Fin()
{
	SCENE->Fin();
}

void FieldScene1::Update()
{
	PLAYER->Update();
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

	PLAYER->Render();
}

void FieldScene1::PreRender()
{
}

void FieldScene1::PostRender()
{
	PLAYER->PostRender();
	_brick->PostRender();
}

void FieldScene1::SceneClear()
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

void FieldScene1::CreateInteractObj()
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
	INTERACTOBJ->SetPlayer(PLAYER);
}
