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
	wstring filePath = L"Maps/BossField1.map";
	_brick->Load(filePath);
	_player->GetFootCollider()->GetTransform()->SetPos(_brick->GetPlayerSpawn());
	_yggdrasil->SetOriginPos(_brick->GetBossSpawn());

	Vector2 temp = _brick->GetDoorSpawn();
	INTERACTOBJ->CreateRandomDoor();
	INTERACTOBJ->GetDoor()->GetTransform()->SetPos(Vector2(temp.x, temp.y + 16));

	temp = _brick->GetChestSpawn();
	INTERACTOBJ->CreateRandomChest();
	INTERACTOBJ->GetChest()->GetTransform()->SetPos(Vector2(temp.x, temp.y + 16));
	INTERACTOBJ->SetPlayer(_player);

	CAMERA->SetTarget(_player->GetBodyCollider()->GetTransform());
	CAMERA->SetOffset(CENTER);
}

void BossScene::Fin()
{
	CAMERA->SetTarget(nullptr);
}

void BossScene::Update()
{
	_player->Update();
	_yggdrasil->Update();
	_brick->Update();
	if (_yggdrasil->GetAlive() == false)
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
}

void BossScene::Render()
{
	_yggdrasil->Render();
	_brick->Render();
	_yggdrasil->HandRender();
	if (_yggdrasil->GetAlive() == false)
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
