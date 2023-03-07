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
	for (const auto& block : _blocks)
		block->Update();
	for (const auto& floor : _floors)
		floor->Update();

	_brick->Update();

	if (KEY_DOWN(VK_F2))
		ActivatePlayer();
	if (KEY_DOWN(VK_F3))
		DeactivatePlayer();

	if (KEY_DOWN('1'))
		_type = EditorType::DRAW;
	else if (KEY_DOWN('2'))
		_type = EditorType::ERASE;
	else if (KEY_DOWN('3'))
		_type = EditorType::DRAG;
	else if (KEY_DOWN('4'))
		_type = EditorType::PLAYERSPAWN;
	else if (KEY_DOWN('5'))
		_type = EditorType::MONSTERSPAWN;
	else if (KEY_DOWN('6'))
		_type = EditorType::BLOCKCOLLIDER;
	else if (KEY_DOWN('7'))
		_type = EditorType::FLOORCOLLIDER;

	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 mousePos = CAMERA->GetWorldMousePos();
		Vector2 tempPos = Vector2((int)(mousePos.x / 100.0f) * 100 + 50, (int)(mousePos.y / 100.0f) * 100 + 50);

		if (_type == EditorType::DRAG)
		{
			_selectedIndex = _brick->SelectBlock(tempPos);
		}
		else if (_type == EditorType::BLOCKCOLLIDER || _type == EditorType::FLOORCOLLIDER)
		{
			_startPos = tempPos;
		}
	}
	if (KEY_PRESS(VK_LBUTTON))
	{
		Vector2 mousePos = CAMERA->GetWorldMousePos();
		Vector2 tempPos = Vector2((int)(mousePos.x / 100.0f) * 100 + 50, (int)(mousePos.y / 100.0f) * 100 + 50);

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
			_brick->SetSpawnPoint(tempPos);
		}
	}

	if (KEY_UP(VK_LBUTTON))
	{
		Vector2 mousePos = CAMERA->GetWorldMousePos();
		Vector2 tempPos = Vector2((int)(mousePos.x / 100.0f) * 100 + 50, (int)(mousePos.y / 100.0f) * 100 + 50);
		_endPos = tempPos;

		if (_type == EditorType::BLOCKCOLLIDER)
		{
			shared_ptr<RectCollider> rect = make_shared<RectCollider>(Vector2(abs(_endPos.x - _startPos.x) + _brick->GetSize().x, abs(_endPos.y - _startPos.y) + _brick->GetSize().y + 20));
			_blocks.emplace_back(rect);
			_blocks.back()->GetTransform()->SetPos(Vector2((_endPos.x + _startPos.x) * 0.5f,(_endPos.y + _startPos.y) * 0.5f - 10.0f));
		}
		else if (_type == EditorType::FLOORCOLLIDER)
		{
			shared_ptr<RectCollider> rect = make_shared<RectCollider>(Vector2(abs(_endPos.x - _startPos.x) + _brick->GetSize().x, abs(_endPos.y - _startPos.y) + _brick->GetSize().y));
			_floors.emplace_back(rect);
			_floors.back()->GetTransform()->SetPos((_endPos + _startPos) * 0.5f);
		}
	}

	if (KEY_PRESS(VK_LCONTROL) && KEY_PRESS('Z'))
	{
		_blocks.pop_back();
		// TODO
	}
	if (KEY_DOWN(VK_CONTROL) && KEY_DOWN('X'))
	{
		_floors.pop_back();
	}
}

void MapEditorTestScene::Render()
{
	for (const auto& block : _blocks)
		block->Render();
	for (const auto& floor : _floors)
		floor->Render();
}

void MapEditorTestScene::PreRender()
{
	_brick->Render();
}

void MapEditorTestScene::PostRender()
{
	_brick->PostRender();
	ImGui::SliderInt("EDIT MODE", &_type, EditorType::DRAW, EditorType::BLOCKCOLLIDER);
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
