#include "framework.h"
#include "MapEditorTestScene.h"

MapEditorTestScene::MapEditorTestScene()
{
	_brick = make_shared<Brick>();

	_playerSpawn = make_shared<Quad>(L"Resources/Texture/SKUL/SkulDead.png");
	_playerSpawn->GetTransform()->SetPos(Vector2(-50, -50));
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
	_playerSpawn->Update();

	Functions();
}

void MapEditorTestScene::Render()
{
	_playerSpawn->Render();
}

void MapEditorTestScene::PreRender()
{
	_brick->Render();
}

void MapEditorTestScene::PostRender()
{
	_brick->PostRender();
	ImGui::SliderInt("EDIT MODE", &_type, EditorType::DRAW, EditorType::FLOORCOLLIDER);
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
	wstring name = L"Maps/Field1.map";
	BinaryWriter writer = BinaryWriter(name);

	vector<BlockData> data = _brick->GetBlockDatas();
	writer.UInt(data.size());
	writer.Byte(&data[0], sizeof(BlockData) * data.size());
	
	Vector2 leftBottom = _brick->GetLeftBottom();
	Vector2 rightTop = _brick->GetRightTop();
	writer.Byte(&leftBottom, sizeof(Vector2));
	writer.Byte(&rightTop, sizeof(Vector2));

	vector<ColliderData> blockData = _brick->GetBlockColliderDatas();
	int size = blockData.size();
	writer.UInt(size);
	if (blockData.size() != 0)
	{
		writer.Byte(&blockData[0], sizeof(ColliderData) * size);
	}
	
	vector<ColliderData> floorData = _brick->GetFloorColliderDatas();
	size = floorData.size();
	writer.UInt(size);
	if (floorData.size() != 0)
	{
		writer.Byte(&floorData[0], sizeof(ColliderData) * size);
	}

	Vector2 spawnPos = _playerSpawn->GetTransform()->GetPos();
	writer.Byte(&spawnPos, sizeof(Vector2));
}

void MapEditorTestScene::Load()
{
	_brick->Load();
	_playerSpawn->GetTransform()->SetPos(_brick->GetPlayerSpawn());
}

void MapEditorTestScene::Functions()
{
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
		Vector2 tempPos = Vector2((int)(mousePos.x / 60.0f) * 60 + 30, (int)(mousePos.y / 60.0f) * 60 + 30);

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
		Vector2 tempPos = Vector2((int)(mousePos.x / 60.0f) * 60 + 30, (int)(mousePos.y / 60.0f) * 60 + 30);

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
			_playerSpawn->GetTransform()->SetPos(tempPos);
		}
	}

	if (KEY_UP(VK_LBUTTON))
	{
		Vector2 mousePos = CAMERA->GetWorldMousePos();
		Vector2 tempPos = Vector2((int)(mousePos.x / 60.0f) * 60 + 30, (int)(mousePos.y / 60.0f) * 60 + 30);
		_endPos = tempPos;

		if (_type == EditorType::BLOCKCOLLIDER)
		{
			_brick->SetBlockCollider(_startPos, _endPos);
		}
		else if (_type == EditorType::FLOORCOLLIDER)
		{
			_brick->SetFloorCollider(_startPos, _endPos);
		}
	}

	if (KEY_PRESS(VK_LCONTROL) && KEY_DOWN('Z'))
	{
		_brick->DeleteBlockCollider();
	}
	if (KEY_PRESS(VK_CONTROL) && KEY_DOWN('X'))
	{
		_brick->DeleteFloorCollider();
	}
}