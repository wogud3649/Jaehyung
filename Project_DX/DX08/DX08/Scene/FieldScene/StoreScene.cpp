#include "framework.h"
#include "StoreScene.h"

StoreScene::StoreScene()
{
	_brick = make_shared<Brick>();
}

StoreScene::~StoreScene()
{
}

void StoreScene::Init()
{
	wstring filePath = L"Maps/Store.map";

	_brick->Load(filePath);

	CreateInteractObj();

	PLAYER->GetFootCollider()->GetTransform()->SetPos(_brick->GetPlayerSpawn());
	
	CAMERA->SetTarget(PLAYER->GetBodyCollider()->GetTransform());

	STORE->SetPlayer(PLAYER);

	SCENE->Init();

	_isClear = false;
}

void StoreScene::Fin()
{
	SCENE->Fin();
}

void StoreScene::Update()
{
	PLAYER->Update();
	STORE->Update();
	_brick->Update();

	INTERACTOBJ->GetDoor()->Update();
}

void StoreScene::Render()
{
	_brick->Render();

	INTERACTOBJ->GetDoor()->Render();

	STORE->Render();
	PLAYER->Render();
}

void StoreScene::PreRender()
{
}

void StoreScene::PostRender()
{
	PLAYER->PostRender();
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
	INTERACTOBJ->SetPlayer(PLAYER);
}