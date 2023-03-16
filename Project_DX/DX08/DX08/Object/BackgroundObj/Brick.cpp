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

		if (_player.expired() == false)
		{
			if (_player.lock()->GetJumpPower() > 0.0f)
				return;
			HIT_RESULT result = floor->TopBlock(_player.lock()->GetFootCollider());
			if (result.dir == Direction::UP)
				_player.lock()->Ground();
		}
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

int Brick::SelectActiveBlock(Vector2 pos, bool activate)
{
	for (int i = 0; i < _activeBlocks.size(); i++)
	{
		if (_activeBlocks[i] == false)
			continue;

		if (_transforms[i]->GetPos() == pos)
		{
			if (activate == false)
				_activeBlocks[i] = false;
			return i;
		}
	}
	return -1;
}

void Brick::Load()
{
	wstring name = L"Maps/Field2.map";
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
		_instanceDatas[index].matrix = XMMatrixTranspose(_transforms[index]->GetMatrix());
		_instanceDatas[index].curFrame = data.curFrame;
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
			temp.curFrame = _instanceDatas[i].curFrame;
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
	_quad = make_shared<Quad>(L"Resources/Texture/Background/Tiles_16x10.png", _maxFrame);
	_size = _quad->GetSize();
	_quad->SetVS(ADD_VS(L"Shader/InstancingVertexShader.hlsl"));
	_quad->SetPS(ADD_PS(L"Shader/InstancingPixelShader.hlsl"));

	for (int i = 0; i < _blockPoolCount; i++)
	{
		Brick::InstanceData instanceData;

		shared_ptr<Transform> transform = make_shared<Transform>();

		transform->SetPos(_outPos);
		instanceData.maxFrame = _maxFrame;
		instanceData.curFrame = { 0,0 };
		instanceData.matrix = XMMatrixTranspose(transform->GetMatrix());

		_instanceDatas.emplace_back(instanceData);
		_transforms.emplace_back(transform);
	}

	_instanceBuffer = make_shared<VertexBuffer>(_instanceDatas.data(), sizeof(InstanceData), _instanceDatas.size(), 0, true);
}

int Brick::GetBlockIndex()
{
	for (int i = 0; i < _blockPoolCount; i++)
	{
		if (_activeBlocks[i] == false)
		{
			_activeBlocks[i] = true;
			return i;
		}
	}
	return -1;
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
