#include "framework.h"
#include "MonsterScene.h"

MonsterScene::MonsterScene()
{
	_mushroomEnt = make_shared<MushroomEnt>();
}

MonsterScene::~MonsterScene()
{
}

void MonsterScene::Update()
{
	_mushroomEnt->Update();
}

void MonsterScene::Render()
{
	_mushroomEnt->Render();
}