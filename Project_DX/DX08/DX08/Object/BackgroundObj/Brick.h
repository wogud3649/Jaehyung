#pragma once
class Brick
{
public:
	struct InstanceData
	{
		XMMATRIX matrix;
		Vector2 maxFrame;
		Vector2 curFrame;
	};

	Brick();
	~Brick();

	void Update();
	void Render();
	void PostRender();

	void SetBlockCollider(Vector2 start, Vector2 end);
	void SetFloorCollider(Vector2 start, Vector2 end);
	void DeleteBlockCollider();
	void DeleteFloorCollider();

	int SelectActiveBlock(Vector2 pos, bool activate = true);

	bool Load(wstring filePath);
	void SpawnMonster();

	vector<BlockData> GetBlockDatas();
	vector<ColliderData> GetBlockColliderDatas();
	vector<ColliderData> GetFloorColliderDatas();
	const vector<shared_ptr<Transform>>& GetTransforms() { return _transforms; }
	vector<InstanceData>& GetInstanceDatas() { return _instanceDatas; }
	shared_ptr<VertexBuffer> GetInstanceBuffer() { return _instanceBuffer; }
	const Vector2& GetSize() { return _size; }
	const Vector2& GetOutPos() { return _outPos; }
	const Vector2& GetMaxFrame() { return _maxFrame; }
	const Vector2& GetCurFrame() { return _curFrame; }
	const Vector2& GetLeftBottom() { return _leftBottom; }
	const Vector2& GetRightTop() { return _rightTop; }
	const Vector2& GetPlayerSpawn() { return _playerSpawn; }
	const Vector2& GetBossSpawn() { return _bossSpawn; }
	const Vector2& GetDoorSpawn() { return _doorSpawn; }
	const Vector2& GetChestSpawn() { return _chestSpawn; }
	const vector<Vector2>& GetMonsterSpawn() { return _monsterSpawn; }
	const UINT& GetACtiveMonsters() { return _activeMonsters; }

	void SetBlockeType(Vector2 curFrame) { _curFrame = curFrame; }
	
	const int& GetBlockPoolCount() { return _blockPoolCount; }
	const int& GetBlockIndex();
	const bool& CheckOverlap(Vector2 pos);
	const bool& CheckActive(int index);

private:
	void CreateBlocks();
	void UpdateBlocks();
	void BlockPlayerCollision(const shared_ptr<RectCollider>& block);
	void BlockMonsterCollision(const shared_ptr<RectCollider>& block);

	void UpdateFloors();
	void FloorPlayerCollision(const shared_ptr<RectCollider>& floor);
	void FloorMonsterCollision(const shared_ptr<RectCollider>& floor);

	void UpdateMonsters();
	bool MonsterHeadCollision(const shared_ptr<MushroomEnt>& mushroomEnt);
	bool MonsterPlayerAttackCollision(const shared_ptr<MushroomEnt>& mushroomEnt);
	bool MonsterPlayerThrowHeadCollision(const shared_ptr<MushroomEnt>& mushroomEnt);
	bool MonsterPlayerFireArrowCollision(const shared_ptr<MushroomEnt>& mushroomEnt);
	bool MonsterPlayerMeteorCollision(const shared_ptr<MushroomEnt>& mushroomEnt, const int& index);

	shared_ptr<Quad> _quad;
	vector<shared_ptr<Transform>> _transforms;
	Vector2 _size = { 32, 32 };
	Vector2 _maxFrame = { 4, 40 };
	Vector2 _curFrame = { 0,0 };
	unsigned int _blockPoolCount = 2000;
	vector<bool> _activeBlocks = vector<bool>(_blockPoolCount, false);
	
	vector<InstanceData> _instanceDatas;
	shared_ptr<VertexBuffer> _instanceBuffer;

	Vector2 _outPos = Vector2(-32, -32);
	Vector2 _leftBottom = { INT_MAX, INT_MAX };
	Vector2 _rightTop = { INT_MIN, INT_MIN };

	Vector2 _playerSpawn = _outPos;
	Vector2 _bossSpawn = _outPos * 15;

	vector<shared_ptr<RectCollider>> _blocks;
	vector<shared_ptr<RectCollider>> _floors;

	vector<shared_ptr<MushroomEnt>> _mushroomEnts;
	vector<Vector2> _monsterSpawn;

	Vector2 _doorSpawn = _outPos * 2;
	Vector2 _chestSpawn = _outPos * 2;

	UINT _activeMonsters = 0;
};