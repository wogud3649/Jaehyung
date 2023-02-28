#include "framework.h"
#include "MapEditorTestScene.h"

MapEditorTestScene::MapEditorTestScene()
{
	_player = make_shared<Advanced_Player>();

	_brick = make_shared<Brick>();
	_brick->SetTarget(_player);

	_background = make_shared<Background>();
	_background->GetTransform()->SetPos(CENTER);
	_background->GetTransform()->UpdateSRT();
	_background->SetPlayer(_player);
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
	_background->Update();
	_brick->Update();
	_player->Update();
	
	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 tempPos = Vector2((int)(MOUSE_POS.x / 30) * 30, (int)(MOUSE_POS.y / 30) * 30);
		_brick->SetPos(tempPos);
	}
}

void MapEditorTestScene::Render()
{
	_player->Render();
}

void MapEditorTestScene::PreRender()
{
	_background->Render();
	_brick->Render();
}

void MapEditorTestScene::PostRender()
{
	_brick->PostRender();
}
