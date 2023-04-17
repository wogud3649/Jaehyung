#include "framework.h"
#include "StoreScene.h"

StoreScene::StoreScene()
{
	_store = make_shared<Store>();

	_player = make_shared<Advanced_Player>();

	_brick = make_shared<Brick>();
	_brick->SetPlayer(_player);
}

StoreScene::~StoreScene()
{
}

void StoreScene::Init()
{
	wstring filePath = L"Maps/Store.map";

	_brick->Load(filePath);

	CreateInteractObj();

	_player->GetFootCollider()->GetTransform()->SetPos(_brick->GetPlayerSpawn());
	
	CAMERA->SetTarget(_player->GetBodyCollider()->GetTransform());

	_store->SetPlayer(_player);
	INVENTORY->SetPlayer(_player);

	SCENE->Init();

	_isClear = false;
}

void StoreScene::Fin()
{
	SCENE->Fin();
}

void StoreScene::Update()
{
	_player->Update();
	_store->Update();
	_brick->Update();

	INTERACTOBJ->GetDoor()->Update();
}

void StoreScene::Render()
{
	_brick->Render();

	INTERACTOBJ->GetDoor()->Render();

	_store->Render();
	_player->Render();
}

void StoreScene::PreRender()
{
}

void StoreScene::PostRender()
{
	_player->PostRender();
	_brick->PostRender();
}

void StoreScene::CreateInteractObj()
{
	Vector2 temp = _brick->GetDoorSpawn();
	INTERACTOBJ->GetDoor()->GetTransform()->SetPos(Vector2(temp.x, temp.y + 16));
	INTERACTOBJ->GetDoor()->Extinct();
	INTERACTOBJ->GetDoor()->Spawn();
	INTERACTOBJ->GetDoor()->SetRandom();
	INTERACTOBJ->GetDoor()->Activate();

	INTERACTOBJ->GetChest()->Extinct();
	INTERACTOBJ->SetPlayer(_player);
}