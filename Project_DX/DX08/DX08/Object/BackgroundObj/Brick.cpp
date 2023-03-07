#include "framework.h"
#include "Brick.h"

Brick::Brick()
{
	CreateBlocks();

	_spawnPoint = make_shared<Quad>(L"Resources/Texture/SKUL/SkulDead.png");
	_spawnPoint->GetTransform()->SetPos(Vector2(-50, -50));
}

Brick::~Brick()
{
}

void Brick::Update()
{
	_spawnPoint->Update();

	if (KEY_DOWN('E'))
	{
		_blockType++;
		_blockType %= _blockShapeType;
	}
}

void Brick::Render()
{
	_spawnPoint->Render();

	_instanceBuffer->IASet(1);

	_quad->SetRender();

	DC->DrawIndexedInstanced(6, _instanceDatas.size(), 0, 0, 0);
}

void Brick::PostRender()
{
	ImGui::SliderInt("BlockType", &_blockType, 0, _blockShapeType - 1);
}

void Brick::Draw(Vector2 pos)
{
	if (CheckOverlap(pos))
		return;

	int minBlockIndex = _blockType * _blockPairNumber;

	int tempIdx = -1;
	for (int i = minBlockIndex; i < minBlockIndex + _blockPairNumber; i++)
	{
		if (_activeBlocks[i] == false)
		{
			tempIdx = i;
			break;
		}
	}
	if (tempIdx == -1)
		return;

	_transforms[tempIdx]->SetPos(pos);
	_transforms[tempIdx]->UpdateSRT();
	_instanceDatas[tempIdx].matrix = XMMatrixTranspose(_transforms[tempIdx]->GetMatrix());
	_instanceBuffer->Update();

	_activeBlocks[tempIdx] = true;
}

void Brick::Erase(Vector2 pos)
{
	for (int i = 0; i < _activeBlocks.size(); i++)
	{
		if (_activeBlocks[i] == false)
			continue;

		if (_transforms[i]->GetPos() == pos)
		{
			_transforms[i]->SetPos(_outPos);
			_transforms[i]->UpdateSRT();
			_instanceDatas[i].matrix = XMMatrixTranspose(_transforms[i]->GetMatrix());
			_instanceBuffer->Update();

			_activeBlocks[i] = false;
		}
	}
}

void Brick::Drag(int index, Vector2 pos)
{
	if (CheckOverlap(pos))
		return;

	_transforms[index]->SetPos(pos);
	_transforms[index]->UpdateSRT();
	_instanceDatas[index].matrix = XMMatrixTranspose(_transforms[index]->GetMatrix());
	_instanceBuffer->Update();

	_activeBlocks[index] = true;
}

void Brick::SetSpawnPoint(Vector2 pos)
{
	_spawnPoint->GetTransform()->SetPos(pos);
}

int Brick::SelectBlock(Vector2 pos)
{
	for (int i = 0; i < _activeBlocks.size(); i++)
	{
		if (_activeBlocks[i] == false)
			continue;

		if (_transforms[i]->GetPos() == pos)
		{
			return i;
		}
	}
	return -1;
}

void Brick::Save()
{
	BinaryWriter writer = BinaryWriter(L"Maps/BossField1.map");

	vector<BlockData> datas;
	BlockData temp;
	int size = 0;
	Vector2 LeftBottom = {INT_MAX, INT_MAX};
	Vector2 RightTop = {0, INT_MIN};

	for (int i = 0; i < _activeBlocks.size(); i++)
	{
		if (_activeBlocks[i])
		{
			temp.index = i;
			temp.pos = _transforms[i]->GetPos();
			datas.emplace_back(temp);
			size++;

			if (LeftBottom.x > temp.pos.x)
				LeftBottom.x = temp.pos.x;
			if (LeftBottom.y > temp.pos.y)
				LeftBottom.y = temp.pos.y;
			if (RightTop.x < temp.pos.x)
				RightTop.x = temp.pos.x;
			if (RightTop.y < temp.pos.y)
				RightTop.y = temp.pos.y;
		}
	}

	writer.UInt(size);
	writer.Byte(&datas[0], sizeof(BlockData) * size);
	writer.Byte(&LeftBottom, sizeof(Vector2));
	writer.Byte(&RightTop, sizeof(Vector2));

	Vector2 tempPos = _spawnPoint->GetTransform()->GetPos();
	writer.Byte(&tempPos, sizeof(Vector2));
}

void Brick::Load()
{
	BinaryReader reader = BinaryReader(L"Maps/BossField1.map");

	int size = reader.UInt();
	vector<BlockData> datas;
	datas.resize(size);
	void* ptr = &datas[0];
	
	reader.Byte(&ptr, sizeof(BlockData) * size);
	for (auto data : datas)
	{
		int index = data.index;
		_activeBlocks[index] = true;
		_transforms[index]->SetPos(data.pos);
		_transforms[index]->UpdateSRT();
		_instanceDatas[index].matrix = XMMatrixTranspose(_transforms[index]->GetMatrix());
		_instanceBuffer->Update();
	}

	Vector2 tempVector;
	ptr = &tempVector;

	reader.Byte(&ptr, sizeof(Vector2));
	CAMERA->SetLeftBottom(Vector2(tempVector.x, tempVector.y - 300));
	reader.Byte(&ptr, sizeof(Vector2));
	CAMERA->SetRightTop(tempVector);

	reader.Byte(&ptr, sizeof(Vector2));
}

void Brick::CreateBlocks()
{
	_quad = make_shared<Quad>(L"Resources/Texture/Background/Grass.png", Vector2(2, 1));
	_size = _quad->GetSize();
	_quad->SetVS(ADD_VS(L"Shader/InstancingVertexShader.hlsl"));
	_quad->SetPS(ADD_PS(L"Shader/InstancingPixelShader.hlsl"));

	for (int i = 0; i < _blockShapeType * _blockPairNumber; i++)
	{
		Brick::InstanceData instanceData;

		shared_ptr<Transform> transform = make_shared<Transform>();

		transform->SetPos(_outPos);
		transform->UpdateSRT();

		int block = i / (_blockPairNumber);

		instanceData.maxFrame = Vector2(_blockShapeType, 1);
		instanceData.curFrame = Vector2(block % _blockShapeType, 0);
		instanceData.matrix = XMMatrixTranspose(transform->GetMatrix());

		_instanceDatas.emplace_back(instanceData);

		_transforms.emplace_back(transform);
	}

	_instanceBuffer = make_shared<VertexBuffer>(_instanceDatas.data(), sizeof(InstanceData), _instanceDatas.size(), 0, true);
}

bool Brick::CheckOverlap(Vector2 pos)
{
	for (int i = 0; i < _activeBlocks.size(); i++)
	{
		if (_activeBlocks[i] == false)
			continue;

		if (_transforms[i]->GetPos() == pos)
		{
			return true;
		}
	}
	return false;
}
