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
	
	for (const auto& monsterSpawn : _monsterSpawn)
	{
		monsterSpawn->Update();
	}

	Functions();
}

void MapEditorTestScene::Render()
{
	for (const auto& monsterSpawn : _monsterSpawn)
	{
		monsterSpawn->Render();
	}

	_playerSpawn->Render();
}

void MapEditorTestScene::PreRender()
{
	_brick->Render();
}

void MapEditorTestScene::PostRender()
{
	ImGui::SliderInt("EDIT MODE", &_type, EditorType::DRAW, EditorType::FLOORCOLLIDER);
	ImGui::SetWindowSize({ 400, 720 });
	ImGui::SetWindowPos({ WIN_WIDTH - 400, 0 });
	if (ImGui::TreeNode("EditTools"))
	{
		if (ImGui::TreeNode("BlockType"))
		{
			ID3D11ShaderResourceView* textureView = SRV_ADD(L"Resources/Texture/Background/Tiles_16x10.png")->GetSRVPointer().Get();

			ImTextureID textureID = (ImTextureID)textureView;

			ImVec2 size = { 32, 32 };

			for (int row = 0; row < 20; row++)
			{
				for (int col = 0; col < 8; col++)
				{
					ImGui::Image((void*)textureID, size, { 0.125f * col, 0.05f * row }, { 0.125f * (col + 1), 0.05f * (row + 1) });
					if (ImGui::IsItemClicked())
					{
						_brick->SetBlockeType({ col, row });
					}

					ImGui::SameLine();
				}
				ImGui::NewLine();
			}

			ImGui::TreePop();
		}

		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Save/Load"))
	{
		if (ImGui::Button("SAVE MAP", { 100, 30 }))
		{
			Save();
			_history = "Saved!!";
		}
		if (ImGui::Button("LOAD MAP", { 100, 30 }))
		{
			Load();
			_history = "Loaded!!";
		}
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("History"))
	{
		ImGui::Text(&_history[0]);

		ImGui::TreePop();
	}
}

void MapEditorTestScene::Save()
{
	wstring name = L"Maps/Field3.map";
	BinaryWriter writer = BinaryWriter(name);

	vector<BlockData> data = _brick->GetBlockDatas();
	writer.UInt(data.size());
	if (data.size() != 0)
	{
		writer.Byte(&data[0], sizeof(BlockData) * data.size());

		Vector2 leftBottom = _brick->GetLeftBottom();
		Vector2 rightTop = _brick->GetRightTop();
		writer.Byte(&leftBottom, sizeof(Vector2));
		writer.Byte(&rightTop, sizeof(Vector2));
	}

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

	size = _monsterSpawn.size();
	writer.UInt(size);
	if (_monsterSpawn.size() != 0)
	{
		vector<Vector2> SpawnPoses;
		for (const auto& monsterSpawn : _monsterSpawn)
			SpawnPoses.emplace_back(monsterSpawn->GetTransform()->GetPos());
		writer.Byte(&SpawnPoses[0], sizeof(Vector2) * size);
	}
}

void MapEditorTestScene::Load()
{
	_brick->Load();
	_playerSpawn->GetTransform()->SetPos(_brick->GetPlayerSpawn());
	
	vector<Vector2> spawnPoses = _brick->GetMonsterSpawn();
	_monsterSpawn.clear();
	if (spawnPoses.size() != 0)
	{
		for (int i = 0; i < spawnPoses.size(); i++)
		{
			shared_ptr<Quad> monster = make_shared<Quad>(L"Resources/Texture/Slime/Dead/Dead6.png");
			Vector2 temp = spawnPoses[i];
			monster->GetTransform()->SetPos(temp);
			_monsterSpawn.emplace_back(monster);
		}
	}
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

	if (KEY_DOWN(VK_LBUTTON) && !ImGui::IsWindowHovered(4))
	{
		Vector2 tempPos = GetTiledPos();

		if (_type == EditorType::DRAG)
		{
			_selectedIndex = _brick->SelectActiveBlock(tempPos);
		}
		else if (_type == EditorType::MONSTERSPAWN)
		{
			for (const auto& spawn : _monsterSpawn)
			{
				if (spawn->GetTransform()->GetPos() == tempPos) // TODO
					return;
			}
			shared_ptr<Quad> monster = make_shared<Quad>(L"Resources/Texture/Slime/Dead/Dead6.png");
			monster->GetTransform()->SetPos(tempPos);
			_monsterSpawn.emplace_back(monster);
		}
		else if (_type == EditorType::BLOCKCOLLIDER || _type == EditorType::FLOORCOLLIDER)
		{
			_startPos = tempPos;
		}
	}

	if (KEY_PRESS(VK_LBUTTON) && !ImGui::IsWindowHovered(4))
	{
		Vector2 tempPos = GetTiledPos();

		if (_type == EditorType::DRAW)
		{
			Draw(tempPos);
		}
		else if (_type == EditorType::ERASE)
		{
			Erase(tempPos);
		}
		else if (_type == EditorType::DRAG)
		{
			if (_selectedIndex != -1)
			{
				Drag(tempPos);
			}
		}
		else if (_type == EditorType::PLAYERSPAWN)
		{
			_playerSpawn->GetTransform()->SetPos(tempPos);
		}
	}

	if (KEY_UP(VK_LBUTTON))
	{
		Vector2 tempPos = GetTiledPos();
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
		if (_type == EditorType::BLOCKCOLLIDER)
			_brick->DeleteBlockCollider();
		else if (_type == EditorType::FLOORCOLLIDER)
			_brick->DeleteFloorCollider();
		else if (_type == EditorType::MONSTERSPAWN)
		{
			if (_monsterSpawn.empty() == false)
			{
				_monsterSpawn.resize(_monsterSpawn.size() - 1);
			}
		}
	}
}

void MapEditorTestScene::Draw(Vector2 pos)
{
	if (_brick->CheckOverlap(pos) == true)
		return;
	
	int index = _brick->GetBlockIndex();
	if (index == -1)
		return;

	_brick->GetTransforms()[index]->SetPos(pos);
	_brick->GetInstanceDatas()[index].curFrame = _brick->GetCurFrame();
	_brick->GetInstanceDatas()[index].matrix = XMMatrixTranspose(_brick->GetTransforms()[index]->GetMatrix());
	_brick->GetInstanceBuffer()->Update();

	_history = "Drawed!!";
}

void MapEditorTestScene::Erase(Vector2 pos)
{
	int index = _brick->SelectActiveBlock(pos, false);
	if (index == -1)
		return;

	_brick->GetTransforms()[index]->SetPos(_brick->GetOutPos());
	_brick->GetInstanceDatas()[index].matrix = XMMatrixTranspose(_brick->GetTransforms()[index]->GetMatrix());
	_brick->GetInstanceBuffer()->Update();

	_history = "Erased!!";
}

void MapEditorTestScene::Drag(Vector2 pos)
{
	if (_brick->CheckOverlap(pos) == true)
		return;
	
	if (_selectedIndex == -1)
		return;

	_brick->GetTransforms()[_selectedIndex]->SetPos(pos);
	_brick->GetInstanceDatas()[_selectedIndex].matrix = XMMatrixTranspose(_brick->GetTransforms()[_selectedIndex]->GetMatrix());
	_brick->GetInstanceBuffer()->Update();

	_history = "Dragged!!";
}

Vector2 MapEditorTestScene::GetTiledPos()
{
	Vector2 mousePos = CAMERA->GetWorldMousePos();
	if (mousePos.x < 0.0f)
		mousePos.x -= 64.0f;
	if (mousePos.y < 0.0f)
		mousePos.y -= 64.0f;
	Vector2 tempPos = Vector2((int)(mousePos.x / 64.0f) * 64 + 32, (int)(mousePos.y / 64.0f) * 64 + 32);

	return tempPos;
}
