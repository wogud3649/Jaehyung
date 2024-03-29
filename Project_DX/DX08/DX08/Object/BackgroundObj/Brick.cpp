#include "framework.h"
#include "Brick.h"

Brick::Brick()
{
	CreateBlocks();
}

Brick::~Brick()
{
}

void Brick::SpawnMonster()
{
	for (int i = 0; i < _monsterSpawn.size(); i++)
	{
		shared_ptr<MushroomEnt> mushroomEnt = make_shared<MushroomEnt>();
		mushroomEnt->SetPos(_monsterSpawn[i]);
		_mushroomEnts.emplace_back(mushroomEnt);
	}
}

void Brick::Update()
{
	UpdateBlocks();
	UpdateFloors();
	UpdateMonsters();
}

void Brick::Render()
{
	_instanceBuffer->IASet(1);

	_quad->SetRender();

	DC->DrawIndexedInstanced(6, _instanceDatas.size(), 0, 0, 0);

	for (auto monster : _mushroomEnts)
		monster->Render();

	for (const auto& block : _blocks)
		block->Render();
	for (const auto& floor : _floors)
		floor->Render();
}

void Brick::PostRender()
{
	for (const auto& mushroomEnt : _mushroomEnts)
		mushroomEnt->PostRender();
}

void Brick::SetBlockCollider(Vector2 start, Vector2 end)
{
	shared_ptr<RectCollider> rect = make_shared<RectCollider>(Vector2(abs(end.x - start.x) + _size.x, abs(end.y - start.y) + _size.y));
	_blocks.emplace_back(rect);
	_blocks.back()->GetTransform()->SetPos(Vector2((end.x + start.x) * 0.5f, (end.y + start.y) * 0.5f - 20.0f));
}

void Brick::SetFloorCollider(Vector2 start, Vector2 end)
{
	shared_ptr<RectCollider> rect = make_shared<RectCollider>(Vector2(abs(end.x - start.x) + _size.x, abs(end.y - start.y) + _size.y * 0.5f));
	_floors.emplace_back(rect);
	_floors.back()->GetTransform()->SetPos(Vector2((end.x + start.x) * 0.5f, (end.y + start.y) * 0.5f));
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
	_floors.resize(_floors.size() - 1);
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

bool Brick::Load(wstring filePath)
{
	if (filePath == L"")
		return false;

	wstring name = filePath;
	BinaryReader reader = BinaryReader(name);

	Vector2 tempVector;
	void* ptr;

	int size = reader.UInt();

	if (size != 0)
	{
		vector<BlockData> datas;
		datas.resize(size);
		ptr = &datas[0];
		reader.Byte(&ptr, sizeof(BlockData) * size);
		
		for (int i = 0; i < _blockPoolCount; i++)
		{
			if (i < size)
			{
				_activeBlocks[i] = true;
				_transforms[i]->SetPos(datas[i].pos);
				_instanceDatas[i].matrix = XMMatrixTranspose(_transforms[i]->GetMatrix());
				_instanceDatas[i].curFrame = datas[i].curFrame;
				_instanceBuffer->Update();
			}
			else
			{
				if (_activeBlocks[i] == false)
					continue;

				_activeBlocks[i] = false;
				_transforms[i]->SetPos(_outPos);
				_instanceDatas[i].matrix = XMMatrixTranspose(_transforms[i]->GetMatrix());
				_instanceDatas[i].curFrame = Vector2(0, 0);
				_instanceBuffer->Update();
			}
		}

		ptr = &tempVector;
		reader.Byte(&ptr, sizeof(Vector2));
		CAMERA->SetLeftBottom(Vector2(tempVector.x, tempVector.y - 200));
		reader.Byte(&ptr, sizeof(Vector2));
		CAMERA->SetRightTop(tempVector);
	}

	size = reader.UInt();

	_blocks.clear();
	if (size != 0)
	{
		vector<ColliderData> blockData;
		blockData.resize(size);
		ptr = &blockData[0];
		UINT stride = sizeof(ColliderData);
		reader.Byte(&ptr, sizeof(ColliderData) * size);
		for (const auto& block : blockData)
		{
			shared_ptr<RectCollider> temp = make_shared<RectCollider>(block.size);
			_blocks.emplace_back(temp);
			_blocks.back()->GetTransform()->SetPos(block.pos);
		}
	}

	size = reader.UInt();

	_floors.clear();
	if (size != 0)
	{
		vector<ColliderData> floorData;
		floorData.resize(size);
		ptr = &floorData[0];
		reader.Byte(&ptr, sizeof(ColliderData) * size);
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

	reader.Byte(&ptr, sizeof(Vector2));
	_bossSpawn = tempVector;

	size = reader.UInt();

	_mushroomEnts.clear();
	_monsterSpawn.clear();
	if (size != 0)
	{
		vector<Vector2> spawnPoses;
		spawnPoses.resize(size);
		ptr = &spawnPoses[0];
		reader.Byte(&ptr, sizeof(Vector2) * size);
		for (const auto& spawnPos : spawnPoses)
		{
			_monsterSpawn.emplace_back(spawnPos);
		}
	}

	ptr = &tempVector;
	reader.Byte(&ptr, sizeof(Vector2));
	_doorSpawn = tempVector;

	ptr = &tempVector;
	reader.Byte(&ptr, sizeof(Vector2));
	_chestSpawn = tempVector;

	return true;
}

vector<BlockData> Brick::GetBlockDatas()
{
	vector<BlockData> datas;
	BlockData temp;
	datas.clear();
	_leftBottom = { INT_MAX, INT_MAX };
	_rightTop = { INT_MIN, INT_MIN };
	for (int i = 0; i < _activeBlocks.size(); i++)
	{
		if (_activeBlocks[i])
		{
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
	_quad = make_shared<Quad>(L"Resources/Texture/Background/Tiles_4x40.png", _maxFrame);
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

void Brick::UpdateBlocks()
{
	for (const auto& block : _blocks)
	{
		block->Update();

		BlockPlayerCollision(block);
		BlockMonsterCollision(block);
	}
}

void Brick::BlockPlayerCollision(const shared_ptr<RectCollider>& block)
{
	HIT_RESULT result = block->Block(PLAYER->GetFootCollider());
	if (result.isHit == false)
		return;
	
	if (result.dir == Direction::UP)
		PLAYER->Ground();
}

void Brick::BlockMonsterCollision(const shared_ptr<RectCollider>& block)
{
	for (auto mushroomEnt : _mushroomEnts)
	{
		HIT_RESULT result = block->Block(mushroomEnt->GetStandBodyCol());
		if (result.isHit == false)
			continue;
		
		float entX = mushroomEnt->GetStandBodyCol()->GetTransform()->GetWorldPos().x;
		float blockX = block->GetTransform()->GetWorldPos().x;
		if (result.dir == Direction::UP)
		{
			if (result.distance.x + 32 > block->GetWorldHalfSize().x)
				mushroomEnt->Flip(Direction::LEFT);
			else if (result.distance.x - 32 < -block->GetWorldHalfSize().x)
				mushroomEnt->Flip(Direction::RIGHT);
			mushroomEnt->Ground();
		}
		else if (result.dir == Direction::LEFT || result.dir == Direction::RIGHT)
			mushroomEnt->Flip(result.dir);
	}
}

void Brick::UpdateFloors()
{
	for (const auto& floor : _floors)
	{
		floor->Update();

		FloorPlayerCollision(floor);
		FloorMonsterCollision(floor);
	}
}

void Brick::FloorPlayerCollision(const shared_ptr<RectCollider>& floor)
{
	if (PLAYER->GetJumpPower() > 0.0f)
		return;
	if (PLAYER->GetIsBungee())
		return;
	
	HIT_RESULT result = floor->TopBlock(PLAYER->GetFootCollider());
	if (result.dir == Direction::UP)
		PLAYER->Ground();
}

void Brick::FloorMonsterCollision(const shared_ptr<RectCollider>& floor)
{
	for (auto mushroomEnt : _mushroomEnts)
	{
		HIT_RESULT result = floor->TopBlock(mushroomEnt->GetStandBodyCol());
		if (result.isHit == false)
			continue;
		
		float entX = mushroomEnt->GetStandBodyCol()->GetTransform()->GetWorldPos().x;
		float blockX = floor->GetTransform()->GetWorldPos().x;
		if (result.dir != Direction::UP)
			continue;
		
		if (result.distance.x + 32 > floor->GetWorldHalfSize().x)
			mushroomEnt->Flip(Direction::LEFT);
		else if (result.distance.x - 32 < -floor->GetWorldHalfSize().x)
			mushroomEnt->Flip(Direction::RIGHT);
		mushroomEnt->Ground();
	}
}

void Brick::UpdateMonsters()
{
	bool headHit = false;
	bool attackHit = false;
	bool throwHeadHit = false;
	bool fireArrowHit = false;
	bool meteorHit = false;
	int index = -1;
	UINT activeMonsters = 0;

	for (auto mushroomEnt : _mushroomEnts)
	{
		mushroomEnt->Update();

		if (mushroomEnt->GetAlive() == false)
			continue;
		
		if (MonsterHeadCollision(mushroomEnt))
			headHit = true;
		activeMonsters++;

		if (mushroomEnt->GetDuckBodyCol()->GetActive() == false)
			continue;

		if (MonsterPlayerAttackCollision(mushroomEnt))
			attackHit = true;
		if (MonsterPlayerThrowHeadCollision(mushroomEnt))
			throwHeadHit = true;
		if (MonsterPlayerFireArrowCollision(mushroomEnt))
			fireArrowHit = true;

		for (int i = 0; i < 3; i++)
			if (MonsterPlayerMeteorCollision(mushroomEnt, i))
			{
				meteorHit = true;
				index = i;
			}
	}

	_activeMonsters = activeMonsters;

	if (headHit)
		PLAYER->Bounce();
	if (attackHit)
		PLAYER->AttackHit();
	if (throwHeadHit)
		PLAYER->ThrowHeadHit();
	if (fireArrowHit)
		PLAYER->FireArrowHit();
	if (meteorHit)
		PLAYER->MeteorHit(index);
}

bool Brick::MonsterHeadCollision(const shared_ptr<MushroomEnt>& mushroomEnt)
{
	if (mushroomEnt->GetHeadCol()->IsCollision(PLAYER->GetFootCollider()).isHit == false || PLAYER->GetJumpPower() >= 0.0f || mushroomEnt->GetHeadCol()->GetActive() == false)
		return false;

	mushroomEnt->Duck();
	return true;
}

bool Brick::MonsterPlayerAttackCollision(const shared_ptr<MushroomEnt>& mushroomEnt)
{
	if (PLAYER->GetAttackCol()->GetActive() == false)
		return false;
	
	HIT_RESULT result = mushroomEnt->GetDuckBodyCol()->IsCollision(PLAYER->GetAttackCol());
	if (result.isHit == false)
		return false;
	
	mushroomEnt->Damaged(PLAYER->GetAttackDamage());
	return true;
}

bool Brick::MonsterPlayerThrowHeadCollision(const shared_ptr<MushroomEnt>& mushroomEnt)
{
	if (PLAYER->GetThrowHeadCol()->GetActive() == false)
		return false;
	
	HIT_RESULT result = mushroomEnt->GetDuckBodyCol()->IsCollision(PLAYER->GetThrowHeadCol());
	if (result.isHit == false)
		return false;

	mushroomEnt->Damaged(PLAYER->GetSkillDamage());
	return true;
}

bool Brick::MonsterPlayerFireArrowCollision(const shared_ptr<MushroomEnt>& mushroomEnt)
{
	if (PLAYER->GetArrowCol()->GetActive() == false)
		return false;
	
	HIT_RESULT result = mushroomEnt->GetDuckBodyCol()->IsCollision(PLAYER->GetArrowCol());
	if (result.isHit == false)
		return false;

	mushroomEnt->Damaged(PLAYER->GetSkillDamage());
	return true;
}

bool Brick::MonsterPlayerMeteorCollision(const shared_ptr<MushroomEnt>& mushroomEnt, const int& index)
{
	vector<shared_ptr<CircleCollider>> cols = PLAYER->GetMeteorCols();

	if (cols[index]->GetActive() == false)
		return false;
	
	HIT_RESULT result = mushroomEnt->GetDuckBodyCol()->IsCollision(cols[index]);
	if (result.isHit == false)
		return false;
	
	mushroomEnt->Damaged(PLAYER->GetSkillDamage());
	return true;
}

const int& Brick::GetBlockIndex()
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

const bool& Brick::CheckOverlap(Vector2 pos)
{
	for (int i = 0; i < _activeBlocks.size() - 1; i++)
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

const bool& Brick::CheckActive(int index)
{
	return _activeBlocks[index];
}
