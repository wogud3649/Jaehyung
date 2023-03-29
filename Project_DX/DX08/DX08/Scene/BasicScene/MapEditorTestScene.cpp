#include "framework.h"
#include "MapEditorTestScene.h"

MapEditorTestScene::MapEditorTestScene()
{
	_brick = make_shared<Brick>();

	_playerSpawn = make_shared<Quad>(L"Resources/Texture/SKUL/SkulDead.png");
	_playerSpawn->GetTransform()->SetPos(_brick->GetOutPos());

	_bossSpawn = make_shared<Quad>(L"Resources/Texture/Boss/Yggdrasil/yggdrasil.png");
	_bossSpawn->GetTransform()->SetPos(_brick->GetOutPos() * 15);
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
	_bossSpawn->Update();
	
	for (const auto& monsterSpawn : _monsterSpawn)
		monsterSpawn->Update();

	Functions();
}

void MapEditorTestScene::Render()
{
	_bossSpawn->Render();

	for (const auto& monsterSpawn : _monsterSpawn)
		monsterSpawn->Render();

	_playerSpawn->Render();

	_brick->Render();
}

void MapEditorTestScene::PreRender()
{
}

void MapEditorTestScene::PostRender()
{
	ImGui::Begin("MapEditorScene", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
	ImGui::SetWindowFontScale(2.0f);
	string type = "Type : " + _curType;
	ImGui::Text(&type[0]);
	ImGui::SetWindowFontScale(1.0f);
	ImGui::SetWindowPos({ WIN_WIDTH - 320, 0 });
	ImGui::SetWindowSize({ 320, 720 });
	ImGui::SetNextItemOpen(true);
	if (ImGui::TreeNode("EditTools"))
	{
		// FirstLine
		{
			if (ImGui::Button("Draw", { 80, 30 }))
			{
				_type = EditorType::DRAW;
				_curType = "DRAW";
				_indicatorActive = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Erase", { 80, 30 }))
			{
				_type = EditorType::ERASE;
				_curType = "ERASE";
				_indicatorActive = false;
				ResetIndicator();
			}
			ImGui::SameLine();
			if (ImGui::Button("Drag", { 80, 30 }))
			{
				_type = EditorType::DRAG;
				_curType = "DRAG";
				_indicatorActive = false;
				ResetIndicator();
			}
			ImGui::SameLine();
			ImGui::NewLine();
		}
		// Second Line
		{
			if (ImGui::Button("Player", { 80, 30 }))
			{
				_type = EditorType::PLAYERSPAWN;
				_curType = "PLAYER";
				_indicatorActive = false;
				ResetIndicator();
			}
			ImGui::SameLine();
			if (ImGui::Button("Monster", { 80, 30 }))
			{
				_type = EditorType::MONSTERSPAWN;
				_curType = "MONSTER";
				_indicatorActive = false;
				ResetIndicator();
			}
			ImGui::SameLine();
			if (ImGui::Button("Boss", { 80, 30 }))
			{
				_type = EditorType::BOSSSPAWN;
				_curType = "BOSS";
				_indicatorActive = false;
				ResetIndicator();
			}
			ImGui::SameLine();
			ImGui::NewLine();
		}
		// Third Line
		{
			if (ImGui::Button("BlockCol", { 80, 30 }))
			{
				_type = EditorType::BLOCKCOLLIDER;
				_curType = "BLOCKCOL";
				_indicatorActive = false;
				ResetIndicator();
			}
			ImGui::SameLine();
			if (ImGui::Button("FloorCol", { 80, 30 }))
			{
				_type = EditorType::FLOORCOLLIDER;
				_curType = "FLOORCOL";
				_indicatorActive = false;
				ResetIndicator();
			}
			ImGui::SameLine();
			ImGui::NewLine();
		}

		ImGui::SetNextItemOpen(true);
		if (ImGui::TreeNode("BlockType"))
		{
			ID3D11ShaderResourceView* textureView = SRV_ADD(L"Resources/Texture/Background/Tiles_4x40.png")->GetSRVPointer().Get();

			ImTextureID textureID = (ImTextureID)textureView;

			ImVec2 size = { 32, 32 };

			ImGui::BeginChild("scroll_bar", { 200,180 }, false, ImGuiWindowFlags_AlwaysVerticalScrollbar);

			for (int row = 0; row < _brick->GetMaxFrame().y; row++)
			{
				for (int col = 0; col < _brick->GetMaxFrame().x; col++)
				{
					ImGui::Image((void*)textureID, size, { float(1 / _brick->GetMaxFrame().x) * col, float(1 / _brick->GetMaxFrame().y) * row }, { float(1 / _brick->GetMaxFrame().x) * (col + 1), float(1 / _brick->GetMaxFrame().y) * (row + 1) });
					if (ImGui::IsItemClicked())
					{
						_brick->SetBlockeType({ col, row });
						_type = EditorType::DRAW;
						_curType = "DRAW";
					}

					ImGui::SameLine();
				}
				ImGui::NewLine();
			}

			ImGui::EndChild();
			ImGui::TreePop();
		}

		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Save/Load"))
	{
		ImGuiFileDialog* fileDialog = ImGuiFileDialog::Instance();

		fileDialog->OpenDialog("ChooseFileDlgKey", "Select File", ".map", "./Maps/");
		ImGui::SetNextItemOpen(true);
		if (fileDialog->Display("ChooseFileDlgKey"))
		{
			_curFilePath = fileDialog->GetFilePathName();
		}
		if (ImGui::Button("SAVE MAP", { 100, 30 }))
		{
			bool save = Save();
			if (save == true)
				_history = "Saved!!";
			else
				_history = "SaveFailed!!";
		}
		if (ImGui::Button("LOAD MAP", { 100, 30 }))
		{
			bool load = Load();
			if (load == true)
				_history = "Loaded!!";
			else
				_history = "LoadFailed!!";
		}
		ImGui::TreePop();
	}
	ImGui::End();

	ImGui::Begin("Log");

	string history = "Log : " + _history;
	ImGui::Text(&history[0]);

	string filePath = "FilePath : " + _curFilePath;
	ImGui::Text(&filePath[0]);

	ImGui::End();
}

bool MapEditorTestScene::Save()
{
	if (_curFilePath == "")
		return false;

	wstring filePath = wstring(_curFilePath.begin(),_curFilePath.end());
	BinaryWriter writer = BinaryWriter(filePath);

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

	spawnPos = _bossSpawn->GetTransform()->GetPos();
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

	return true;
}

bool MapEditorTestScene::Load()
{
	wstring filePath = wstring(_curFilePath.begin(), _curFilePath.end());
	bool load = _brick->Load(filePath);
	_playerSpawn->GetTransform()->SetPos(_brick->GetPlayerSpawn());
	_bossSpawn->GetTransform()->SetPos(_brick->GetBossSpawn());
	
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

	return load;
}

void MapEditorTestScene::Functions()
{
	_isHovered = ImGui::IsWindowHovered(4) || ImGui::IsAnyItemHovered();

	Indicator();

	if (KEY_DOWN(VK_LBUTTON) && _isHovered == false)
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
				if (spawn->GetTransform()->GetPos() == tempPos)
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

	if (KEY_PRESS(VK_LBUTTON) && _isHovered == false)
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
		else if (_type == EditorType::BOSSSPAWN)
		{
			_bossSpawn->GetTransform()->SetPos(tempPos);
		}
	}

	if (KEY_UP(VK_LBUTTON) && _isHovered == false)
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
		else if (_type == EditorType::BOSSSPAWN)
		{
			_bossSpawn->GetTransform()->SetPos(_brick->GetOutPos() * 15);
		}
	}
}

void MapEditorTestScene::Indicator()
{
	if (_indicatorActive == false)
		return;

	int index = _brick->GetBlockPoolCount() - 1;
	if (_brick->CheckActive(index))
		return;

	_brick->GetTransforms()[index]->SetPos(CAMERA->GetWorldMousePos());
	_brick->GetInstanceDatas()[index].curFrame = _brick->GetCurFrame();
	_brick->GetInstanceDatas()[index].matrix = XMMatrixTranspose(_brick->GetTransforms()[index]->GetMatrix());
	_brick->GetInstanceBuffer()->Update();
}

void MapEditorTestScene::ResetIndicator()
{
	int index = _brick->GetBlockPoolCount() - 1;
	if (_brick->CheckActive(index))
		return;

	_brick->GetTransforms()[index]->SetPos(_brick->GetOutPos());
	_brick->GetInstanceDatas()[index].matrix = XMMatrixTranspose(_brick->GetTransforms()[index]->GetMatrix());
	_brick->GetInstanceBuffer()->Update();
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
