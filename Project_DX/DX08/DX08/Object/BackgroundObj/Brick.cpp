#include "framework.h"
#include "Brick.h"

Brick::Brick()
{
	CreateBlocks();

	_spawnPoint = make_shared<Quad>(L"Resources/Texture/SKUL/SkulDead.png");
	_spawnPoint->GetTransform()->SetPos(Vector2(-30, -30));
}

Brick::~Brick()
{
}

void Brick::Update()
{
	_spawnPoint->Update();

	for (const auto& col : _cols)
	{
		col->Update();
	}

	if (KEY_DOWN('E'))
	{
		_blockType++;
		_blockType %= _blockShapeType;
	}

	if (_player.expired() == false)
	{
		for (int i = 0; i < _cols.size(); i++)
		{
			if (_activeBlocks[i] == false)
				continue;

			int tempIdx = i / _blockPairNumber;
			if (tempIdx == 0)
			{
				HIT_RESULT result = _cols[i]->Block(_player.lock()->GetFootCollider());
				if (result.dir == Direction::UP)
					_player.lock()->Ground();
				if (result.dir == Direction::DOWN)
					_player.lock()->Beat();
			}
			else
			{
				if (_player.lock()->GetJumpPower() >= 0.0f)
					return;

				HIT_RESULT result = _cols[i]->TopBlock(_player.lock()->GetFootCollider());
				if (result.dir == Direction::UP)
					_player.lock()->Ground();
			}
		}
	}
}

void Brick::Render()
{
	_spawnPoint->Render();

	_instanceBuffer->IASet(1);

	_quad->SetRender();

	DC->DrawIndexedInstanced(6, _instanceDatas.size(), 0, 0, 0);

	for (const auto& col : _cols)
	{
		col->Render();
	}
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
	BinaryWriter writer = BinaryWriter(L"Maps/Field4.map");

	vector<BlockData> datas;
	BlockData temp;
	UINT size = 0;

	for (int i = 0; i < _activeBlocks.size(); i++)
	{
		if (_activeBlocks[i])
		{
			temp.index = i;
			temp.pos = _transforms[i]->GetPos();
			datas.emplace_back(temp);
			size++;
		}
	}

	writer.UInt(size);
	writer.Byte(&datas[0], sizeof(BlockData) * size);

	Vector2 tempPos = _spawnPoint->GetTransform()->GetPos();
	writer.Byte(&tempPos, sizeof(Vector2));
}

void Brick::Load()
{
	BinaryReader reader = BinaryReader(L"Maps/Field4.map");

	UINT size = reader.UInt();
	vector<BlockData> datas;
	datas.reserve(size);

	void* ptr = &datas[0];
	
	reader.Byte((void**)&ptr, sizeof(BlockData) * size);

	// TODO

	Vector2 tempVector;

	tempVector.x = reader.Int();
	tempVector.y = reader.Int();
	_spawnPoint->GetTransform()->SetPos(tempVector);
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

		Vector2 colSize;
		Vector2 colPos;

		shared_ptr<Transform> transform = make_shared<Transform>();

		transform->SetPos(_outPos);
		transform->UpdateSRT();

		int block = i / (_blockPairNumber);
		switch (block % _blockShapeType)
		{
		case 0:
			colSize = Vector2(_size.x, _size.y + 30.0f);
			colPos = Vector2(0.0f, -15.0f);
			break;
		case 1:
			colSize = Vector2(_size.x, _size.y * 0.5f + 20.0f);
			colPos = Vector2(0, 5);
			break;
		default:
			break;
		}

		instanceData.maxFrame = Vector2(_blockShapeType, 1);
		instanceData.curFrame = Vector2(block % _blockShapeType, 0);
		instanceData.matrix = XMMatrixTranspose(transform->GetMatrix());

		_instanceDatas.emplace_back(instanceData);

		_transforms.emplace_back(transform);

		shared_ptr<RectCollider> col = make_shared<RectCollider>(colSize);
		_cols.emplace_back(col);
		_cols[i]->GetTransform()->SetParent(_transforms[i]);
		_cols[i]->GetTransform()->Move(colPos);
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
