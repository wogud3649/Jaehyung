#include "framework.h"
#include "Brick.h"

Brick::Brick()
{
	CreateBlocks();
}

Brick::~Brick()
{
}

void Brick::Update()
{
	for (const auto& block : _blocks)
	{
		block->Update();
		if (_player.expired() == false)
		{
			HIT_RESULT result = block->Block(_player.lock()->GetFootCollider());
			if (result.dir == Direction::UP)
				_player.lock()->Ground();
		}
	}
	for (const auto& floor : _floors)
	{
		floor->Update();
		if (_player.lock()->GetJumpPower() > 0.0f)
			return;
		if (_player.expired() == false)
		{
			HIT_RESULT result = floor->TopBlock(_player.lock()->GetFootCollider());
			if (result.dir == Direction::UP)
				_player.lock()->Ground();
		}
	}

	if (KEY_DOWN('E'))
	{
		_blockType++;
		_blockType %= _blockShapeType;
	}
}

void Brick::Render()
{
	_instanceBuffer->IASet(1);

	_quad->SetRender();

	DC->DrawIndexedInstanced(6, _instanceDatas.size(), 0, 0, 0);

	for (const auto& block : _blocks)
		block->Render();
	for (const auto& floor : _floors)
		floor->Render();
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

void Brick::SetBlockCollider(Vector2 start, Vector2 end)
{
	shared_ptr<RectCollider> rect = make_shared<RectCollider>(Vector2(abs(end.x - start.x) + _size.x, abs(end.y - start.y) + _size.y + 20));
	_blocks.emplace_back(rect);
	_blocks.back()->GetTransform()->SetPos(Vector2((end.x + start.x) * 0.5f, (end.y + start.y) * 0.5f - 10.0f));
}

void Brick::SetFloorCollider(Vector2 start, Vector2 end)
{
	shared_ptr<RectCollider> rect = make_shared<RectCollider>(Vector2(abs(end.x - start.x) + _size.x, abs(end.y - start.y) + _size.y * 0.5f));
	_floors.emplace_back(rect);
	_floors.back()->GetTransform()->SetPos(Vector2((end.x + start.x) * 0.5f, (end.y + start.y) * 0.5f + 15.0f));
}

void Brick::DeleteBlockCollider()
{
	if (_blocks.empty())
		return;
	_blocks.resize(_blocks.size() - 1);
}

void Brick::DeleteFloorCollider()
{
	if (_floors.empty())
		return;
	_floors.resize(_blocks.size() - 1);
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

void Brick::Load()
{
	wstring name = L"Maps/Field1.map";
	BinaryReader reader = BinaryReader(name);

	void* ptr;

	int size = reader.UInt();

	vector<BlockData> datas;
	datas.resize(size);
	ptr = &datas[0];
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
	CAMERA->SetLeftBottom(Vector2(tempVector.x, tempVector.y - 200));
	reader.Byte(&ptr, sizeof(Vector2));
	CAMERA->SetRightTop(tempVector);

	size = reader.UInt();

	if (size != 0)
	{
		vector<ColliderData> blockData;
		blockData.resize(size);
		ptr = &blockData[0];
		UINT stride = sizeof(ColliderData);
		reader.Byte(&ptr, sizeof(ColliderData) * size);
		_blocks.clear();
		for (const auto& block : blockData)
		{
			shared_ptr<RectCollider> temp = make_shared<RectCollider>(block.size);
			_blocks.emplace_back(temp);
			_blocks.back()->GetTransform()->SetPos(block.pos);
		}
	}

	size = reader.UInt();

	if (size != 0)
	{
		vector<ColliderData> floorData;
		floorData.resize(size);
		ptr = &floorData[0];
		reader.Byte(&ptr, sizeof(ColliderData) * size);
		_floors.clear();
		for (const auto& floor : floorData)
		{
			shared_ptr<RectCollider> temp = make_shared<RectCollider>(floor.size);
			_floors.emplace_back(temp);
			_floors.back()->GetTransform()->SetPos(floor.pos);
		}
	}

	ptr = &tempVector;
	reader.Byte(&ptr, sizeof(Vector2));
	_playerSpawn = tempVector;

	size = reader.UInt();

	if (size != 0)
	{
		vector<Vector2> spawnPoses;
		spawnPoses.resize(size);
		ptr = &spawnPoses[0];
		reader.Byte(&ptr, sizeof(Vector2) * size);
		_monsterSpawn.clear();
		for (const auto& spawnPos : spawnPoses)
		{
			_monsterSpawn.emplace_back(spawnPos);
		}
	}
}

vector<BlockData> Brick::GetBlockDatas()
{
	vector<BlockData> datas;
	BlockData temp;

	for (int i = 0; i < _activeBlocks.size(); i++)
	{
		if (_activeBlocks[i])
		{
			temp.index = i;
			temp.pos = _transforms[i]->GetPos();
			datas.emplace_back(temp);

			if (_leftBottom.x > temp.pos.x)
				_leftBottom.x = temp.pos.x;
			if (_leftBottom.y > temp.pos.y)
				_leftBottom.y = temp.pos.y;
			if (_rightTop.x < temp.pos.x)
				_rightTop.x = temp.pos.x;
			if (_rightTop.y < temp.pos.y)
				_rightTop.y = temp.pos.y;
		}
	}

	return datas;
}

vector<ColliderData> Brick::GetBlockColliderDatas()
{
	vector<ColliderData> datas;
	ColliderData temp;

	for (const auto& block : _blocks)
	{
		temp.size = block->GetSize();
		temp.pos = block->GetTransform()->GetWorldPos();
		datas.emplace_back(temp);
	}

	return datas;
}

vector<ColliderData> Brick::GetFloorColliderDatas()
{
	vector<ColliderData> datas;
	ColliderData temp;

	for (const auto& floor : _floors)
	{
		temp.size = floor->GetSize();
		temp.pos = floor->GetTransform()->GetWorldPos();
		datas.emplace_back(temp);
	}

	return datas;
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
