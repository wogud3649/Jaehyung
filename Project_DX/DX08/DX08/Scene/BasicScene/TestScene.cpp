#include "framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	_player = make_shared<Advanced_Player>();

	_brick = make_shared<Brick>();
	_brick->SetPlayer(_player);
}

TestScene::~TestScene()
{
}

void TestScene::Init()
{
	if (_filePath == L"")
		_filePath = L"Maps/Field1.map";

	wstring filePath = _filePath;

	_brick->Load(filePath);

	_player->GetFootCollider()->GetTransform()->SetPos(_brick->GetPlayerSpawn());
	_player->GetFootCollider()->GetTransform()->UpdateSRT();

	vector<Vector2> monsterSpawn = _brick->GetMonsterSpawn();
	for (int i = 0; i < monsterSpawn.size(); i++)
	{
		shared_ptr<MushroomEnt> mushroomEnt = make_shared<MushroomEnt>();
		mushroomEnt->SetPos(monsterSpawn[i]);
		mushroomEnt->SetPlayer(_player);
		_mushroomEnts.emplace_back(mushroomEnt);
	}

	CAMERA->SetTarget(_player->GetBodyCollider()->GetTransform());
	CAMERA->SetOffset(CENTER);
}

void TestScene::Fin()
{
	CAMERA->SetTarget(nullptr);
	_mushroomEnts.clear();
}

void TestScene::Update()
{
	_player->Update();
	_brick->Update();

	for (auto monster : _mushroomEnts)
		monster->Update();
}

void TestScene::Render()
{
	for (auto monster : _mushroomEnts)
		monster->Render();

	_player->Render();
}

void TestScene::PreRender()
{
	_brick->Render();
}

void TestScene::PostRender()
{
}
