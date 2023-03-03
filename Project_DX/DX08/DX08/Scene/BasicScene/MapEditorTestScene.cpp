#include "framework.h"
#include "MapEditorTestScene.h"

MapEditorTestScene::MapEditorTestScene()
{
	_player = make_shared<Advanced_Player>();

	_brick = make_shared<Brick>();
	_brick->SetTarget(_player);
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
	if (_playerActive)
		_player->Update();

	if (KEY_DOWN(VK_F2))
		ActivatePlayer();
	if (KEY_DOWN(VK_F3))
		DeactivatePlayer();

	if (KEY_DOWN('1'))
	{
		_type = EditorType::DRAW;
	}
	if (KEY_DOWN('2'))
	{
		_type = EditorType::ERASE;
	}
	if (KEY_DOWN('3'))
	{
		_type = EditorType::DRAG;
	}
	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 tempPos = Vector2((int)(MOUSE_POS.x / 60) * 60 + 30, (int)(MOUSE_POS.y / 60) * 60 + 30);
		if (_type == EditorType::DRAG)
		{
			_selectedIndex = _brick->SelectBlock(tempPos);
		}
	}
	if (KEY_PRESS(VK_LBUTTON))
	{
		Vector2 tempPos = Vector2((int)(MOUSE_POS.x / 60) * 60 + 30, (int)(MOUSE_POS.y / 60) * 60 + 30);
		if (_type == EditorType::DRAW)
		{
			_brick->Draw(tempPos);
		}
		else if (_type == EditorType::ERASE)
		{
			_brick->Erase(tempPos);
		}
		else if (_type == EditorType::DRAG)
		{
			if (_selectedIndex == -1)
				return;

			_brick->Drag(_selectedIndex, tempPos);
		}
	}
}

void MapEditorTestScene::Render()
{
	_player->Render();
}

void MapEditorTestScene::PreRender()
{
	_brick->Render();
}

void MapEditorTestScene::PostRender()
{
	_brick->PostRender();
	ImGui::SliderInt("Type", &(_type), EditorType::DRAW, EditorType::DRAG);
	if (ImGui::Button("SAVE MAP", { 100, 30 }))
	{
		Save();
	}
	if (ImGui::Button("LOAD MAP", { 100, 30 }))
	{
		Load();
	}

}

void MapEditorTestScene::Save()
{
	_brick->Save();
}

void MapEditorTestScene::Load()
{
	_brick->Load();
}

void MapEditorTestScene::ActivatePlayer()
{
	_player->GetFootCollider()->GetTransform()->SetPos(CENTER);
	_playerActive = true;
}

void MapEditorTestScene::DeactivatePlayer()
{
	_playerActive = false;
}
