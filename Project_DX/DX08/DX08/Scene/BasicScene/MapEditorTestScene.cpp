#include "framework.h"
#include "MapEditorTestScene.h"

MapEditorTestScene::MapEditorTestScene()
{
	_brick = make_shared<Brick>();
}

MapEditorTestScene::~MapEditorTestScene()
{
}

void MapEditorTestScene::Init()
{
}

void MapEditorTestScene::Fin()
{
}

void MapEditorTestScene::Update()
{
	_brick->Update();
}

void MapEditorTestScene::Render()
{
	_brick->Render();
}

void MapEditorTestScene::PreRender()
{
}

void MapEditorTestScene::PostRender()
{
	_brick->PostRender();
}
