#include "framework.h"
#include "BossScene.h"

BossScene::BossScene()
{
	_brick = make_shared<Brick>();

	_healthBar = make_shared<Slider>(L"Resources/Texture/UI/BossHealthBar.png");
	_healthBar->SetOpaque(0.9f);
	Vector2 tempPos = Vector2(CENTER.x, CENTER.y + 300.0f);
	_healthBar->SetPos(tempPos);
}

BossScene::~BossScene()
{
}

void BossScene::Init()
{
	YGGDRASIL->Activate();
	wstring filePath = L"Maps/BossField1.map";
	_brick->Load(filePath);

	CreateInteractObj();

	PLAYER->GetFootCollider()->GetTransform()->SetPos(_brick->GetPlayerSpawn());
	YGGDRASIL->SetOriginPos(_brick->GetBossSpawn());

	CAMERA->SetTarget(PLAYER->GetBodyCollider()->GetTransform());

	SCENE->Init();

	_isClear = false;
}

void BossScene::Fin()
{
	SCENE->Fin();
}

void BossScene::Update()
{
	PLAYER->Update();
	YGGDRASIL->Update();

	float ratio = YGGDRASIL->GetHpRatio();
	_healthBar->SetRatio(ratio);
	_healthBar->Update();
	_brick->Update();

	if (_isClear)
	{
		INTERACTOBJ->GetDoor()->Update();
		INTERACTOBJ->GetChest()->Update();
	}

	if (PLAYER->GetAttackCol()->GetActive())
	{
		if (PLAYER->GetAttackCol()->IsCollision(YGGDRASIL->GetHeadCollider()).isHit)
		{
			YGGDRASIL->Damaged(PLAYER->GetAttackDamage());
			PLAYER->AttackHit();
		}
	}

	if (PLAYER->GetThrowHeadCol()->GetActive())
	{
		if (PLAYER->GetThrowHeadCol()->IsCollision(YGGDRASIL->GetHeadCollider()).isHit)
		{
			YGGDRASIL->Damaged(PLAYER->GetSkillDamage());
			PLAYER->ThrowHeadHit();
		}
	}

	if (PLAYER->GetArrowCol()->GetActive())
	{
		if (PLAYER->GetArrowCol()->IsCollision(YGGDRASIL->GetHeadCollider()).isHit)
		{
			YGGDRASIL->Damaged(PLAYER->GetSkillDamage());
			PLAYER->FireArrowHit();
		}
	}

	vector<shared_ptr<CircleCollider>> cols = PLAYER->GetMeteorCols();
	for (int i = 0; i < 3; i++)
	{
		if (cols[i]->GetActive())
		{
			if (cols[i]->IsCollision(YGGDRASIL->GetHeadCollider()).isHit)
			{
				YGGDRASIL->Damaged(PLAYER->GetSkillDamage());
				PLAYER->MeteorHit(i);
			}
		}
	}

	SceneClear();
}

void BossScene::Render()
{
	YGGDRASIL->Render();
	_brick->Render();
	YGGDRASIL->HandRender();

	if (_isClear)
	{
		INTERACTOBJ->GetDoor()->Render();
		INTERACTOBJ->GetChest()->Render();
	}

	PLAYER->Render();
}

void BossScene::PreRender()
{
}

void BossScene::PostRender()
{
	PLAYER->PostRender();

	if (YGGDRASIL->GetDeadDelay() > 0.0f)
	{
		_healthBar->PostRender();
		float ratio = YGGDRASIL->GetDeadDelay() / 3.0f;
	}
}

void BossScene::SceneClear()
{
	if (_isClear)
		return;

	if (YGGDRASIL->GetDeadDelay() < 0.0f)
	{
		INTERACTOBJ->GetDoor()->Spawn();
		INTERACTOBJ->GetChest()->Spawn();
		_isClear = true;
	}
}

void BossScene::CreateInteractObj()
{
	Vector2 temp = _brick->GetDoorSpawn();
	INTERACTOBJ->GetDoor()->GetTransform()->SetPos(Vector2(temp.x, temp.y + 16));
	INTERACTOBJ->GetDoor()->SetRandom();
	INTERACTOBJ->GetDoor()->DeActivate();

	temp = _brick->GetChestSpawn();
	INTERACTOBJ->GetChest()->GetTransform()->SetPos(Vector2(temp.x, temp.y + 16));
	INTERACTOBJ->GetChest()->Extinct();
	INTERACTOBJ->GetChest()->SetRandom();
}
