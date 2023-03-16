#include "framework.h"
#include "BossScene.h"

BossScene::BossScene()
{
	_player = make_shared<Advanced_Player>();
	
	_brick = make_shared<Brick>();
	_brick->SetPlayer(_player);
	_brick->Load();
	_player->GetFootCollider()->GetTransform()->SetPos(_brick->GetPlayerSpawn());

	_yggdrasil = make_shared<Yggdrasil>();
	_yggdrasil->SetTarget(_player);
	_yggdrasil->SetOriginPos(_brick->GetMonsterSpawn()[0]);
}

BossScene::~BossScene()
{
}

void BossScene::Init()
{
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
	_player->Render();
}

void BossScene::PreRender()
{
	_yggdrasil->Render();
	_brick->Render();
}

void BossScene::PostRender()
{
	_player->PostRender();
	_yggdrasil->PostRender();
}
