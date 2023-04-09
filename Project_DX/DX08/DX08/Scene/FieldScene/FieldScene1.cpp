#include "framework.h"
#include "FieldScene1.h"

FieldScene1::FieldScene1()
{
	_player = make_shared<Advanced_Player>();

	INVENTORY->SetPlayer(_player);

	_brick = make_shared<Brick>();
	_brick->SetPlayer(_player);
}

FieldScene1::~FieldScene1()
{
}

void FieldScene1::Init()
{
	int randInt = rand() % 2;

	switch (randInt)
	{
	case 0:
		_filePath = L"Maps/Field1.map";
		break;
	case 1:
		_filePath = L"Maps/Field2.map";
		break;
	default:
		break;
	}

	_brick->Load(_filePath);
	_brick->SpawnMonster();

	Vector2 temp = _brick->GetDoorSpawn();
	INTERACTOBJ->CreateRandomDoor();
	INTERACTOBJ->GetDoor()->GetTransform()->SetPos(Vector2(temp.x, temp.y + 16));
	INTERACTOBJ->SpawnDoor();

	temp = _brick->GetChestSpawn();
	INTERACTOBJ->CreateRandomChest();
	INTERACTOBJ->GetChest()->GetTransform()->SetPos(Vector2(temp.x, temp.y + 16));
	INTERACTOBJ->SetPlayer(_player);

	_player->GetFootCollider()->GetTransform()->SetPos(_brick->GetPlayerSpawn());

	CAMERA->SetTarget(_player->GetBodyCollider()->GetTransform());
	CAMERA->SetOffset(CENTER);

	UI->Init();
}

void FieldScene1::Fin()
{
	CAMERA->SetTarget(nullptr);
	INTERACTOBJ->ExtinctChest();
	INTERACTOBJ->ExtinctDoor();
}

void FieldScene1::Update()
{
	INVENTORY->Update();
	UI->Update();
	if (INVENTORY->IsOpen())
		return;
	_player->Update();
	_brick->Update();
	INTERACTOBJ->GetDoor()->Update();
	INTERACTOBJ->GetChest()->Update();

	if (_brick->GetActiveMonsters() == 0)
	{
		INTERACTOBJ->SpawnChest();
		INTERACTOBJ->ActivateDoor();
	}
}

void FieldScene1::Render()
{
	INTERACTOBJ->GetDoor()->Render();
	INTERACTOBJ->GetChest()->Render();
	_player->Render();
}

void FieldScene1::PreRender()
{
	_brick->Render();
}

void FieldScene1::PostRender()
{
	INVENTORY->PostRender();
	UI->PostRender();
	_player->PostRender();
	_brick->PostRender();
}
