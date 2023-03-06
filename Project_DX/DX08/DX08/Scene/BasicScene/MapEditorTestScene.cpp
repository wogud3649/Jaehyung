#include "framework.h"
#include "MapEditorTestScene.h"

MapEditorTestScene::MapEditorTestScene()
{
	_background = make_shared<Background>();
	_background->Update();

	_brick = make_shared<Brick>();

	_quad = make_shared<Quad>(L"Resources/Texture/SKUL/SkulDead.png");
	_quad->GetTransform()->SetPos(Vector2(-30, -30));

	CAMERA->SetOffset(CENTER);
	CAMERA->SetLeftBottom(_background->LeftBottom());
	CAMERA->SetRightTop(_background->RightTop());
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
	_quad->Update();

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
		Vector2 mousePos = CAMERA->GetWorldMousePos();
		Vector2 tempPos = Vector2((int)(mousePos.x / 60) * 60 + 30, (int)(mousePos.y / 60) * 60 + 30);
		if (_type == EditorType::DRAG)
		{
			_selectedIndex = _brick->SelectBlock(tempPos);
		}
	}
	if (KEY_PRESS(VK_LBUTTON))
	{
		Vector2 mousePos = CAMERA->GetWorldMousePos();
		Vector2 tempPos = Vector2((int)(mousePos.x / 60) * 60 + 30, (int)(mousePos.y / 60) * 60 + 30);
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
		else if (_type == EditorType::PLAYERSPAWN)
		{
			_quad->GetTransform()->SetPos(tempPos);
		}
	}
}

void MapEditorTestScene::Render()
{
	_quad->Render();
}

void MapEditorTestScene::PreRender()
{
	_background->Render();
	_brick->Render();
}

void MapEditorTestScene::PostRender()
{
	_brick->PostRender();
	ImGui::SliderInt("Type", &(_type), EditorType::DRAW, EditorType::MONSTERSPAWN);
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
}

void MapEditorTestScene::DeactivatePlayer()
{
}
