#include "framework.h"
#include "BossScene.h"

BossScene::BossScene()
{
	_player = make_shared<Advanced_Player>();
	
	_brick = make_shared<Brick>();
	_brick->SetPlayer(_player);

	_yggdrasil = make_shared<Yggdrasil>();
	_yggdrasil->SetTarget(_player);
}

BossScene::~BossScene()
{
}

void BossScene::Init()
{
	_yggdrasil->Activate();
	wstring filePath = L"Maps/BossField1.map";
	_brick->Load(filePath);

	CreateInteractObj();

	_player->GetFootCollider()->GetTransform()->SetPos(_brick->GetPlayerSpawn());
	_yggdrasil->SetOriginPos(_brick->GetBossSpawn());

	CAMERA->SetTarget(_player->GetBodyCollider()->GetTransform());

	SCENE->Init();

	_isClear = false;
}

void BossScene::Fin()
{
	SCENE->Fin();
}

void BossScene::Update()
{
	_player->Update();
	_yggdrasil->Update();
	_brick->Update();

	if (_isClear)
	{
		INTERACTOBJ->GetDoor()->Update();
		INTERACTOBJ->GetChest()->Update();
	}

	if (_player->GetAttackCol()->GetActive())
	{
		if (_player->GetAttackCol()->IsCollision(_yggdrasil->GetHeadCollider()).isHit)
		{
			_yggdrasil->Damaged(_player->GetAttackDamage());
			_player->AttackHit();
		}
	}

	if (_player->GetProjCol()->GetActive())
	{
		if (_player->GetProjCol()->IsCollision(_yggdrasil->GetHeadCollider()).isHit)
		{
			_yggdrasil->Damaged(_player->GetProjDamage());
			_player->SkillHit();
		}
	}

	SceneClear();
}

void BossScene::Render()
{
	_yggdrasil->Render();
	_brick->Render();
	_yggdrasil->HandRender();

	if (_isClear)
	{
		INTERACTOBJ->GetDoor()->Render();
		INTERACTOBJ->GetChest()->Render();
	}

	_player->Render();
}

void BossScene::PreRender()
{
}

void BossScene::PostRender()
{
	ImGui::SetWindowSize({ 320, 320 });
	_player->PostRender();
}

void BossScene::SceneClear()
{
	if (_isClear)
		return;

	if (_yggdrasil->GetAlive() == false)
	{
		INTERACTOBJ->GetDoor()->Spawn();
		INTERACTOBJ->GetChest()->Spawn();
		_isClear = true;
	}
}

void BossScene::CreateInteractObj()
{
	Vector2 temp = _brick->GetDoorSpawn();
	INTERACTOBJ->CreateRandomDoor();
	INTERACTOBJ->GetDoor()->GetTransform()->SetPos(Vector2(temp.x, temp.y + 16));

	temp = _brick->GetChestSpawn();
	INTERACTOBJ->CreateRandomChest();
	INTERACTOBJ->GetChest()->GetTransform()->SetPos(Vector2(temp.x, temp.y + 16));
	INTERACTOBJ->SetPlayer(_player);
}
