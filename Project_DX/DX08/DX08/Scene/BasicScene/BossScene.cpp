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

	if (_player->GetAttackCol()->GetActive())
	{
		if (_player->GetAttackCol()->IsCollision(_yggdrasil->GetHeadCollider()))
		{
			_yggdrasil->Damaged(_player->GetAttackDamage());
			_player->AttackHit();
		}
	}

	if (_player->GetProjCol()->GetActive())
	{
		if (_player->GetProjCol()->IsCollision(_yggdrasil->GetHeadCollider()))
		{
			_yggdrasil->Damaged(_player->GetProjDamage());
			_player->SkillHit();
		}
	}
}

void BossScene::Render()
{
	_yggdrasil->Render();
	_player->Render();
}

void BossScene::PreRender()
{
	_brick->Render();
}

void BossScene::PostRender()
{
	ImGui::SetWindowSize({ 320, 320 });
	_player->PostRender();
	_yggdrasil->PostRender();
}
