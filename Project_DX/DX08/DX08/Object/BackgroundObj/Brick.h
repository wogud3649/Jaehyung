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

	void SetPlayer(shared_ptr<Advanced_Player> player) { _player = player; }

	void SetBlockCollider(Vector2 start, Vector2 end);
	void SetFloorCollider(Vector2 start, Vector2 end);
	void DeleteBlockCollider();
	void DeleteFloorCollider();

	int SelectActiveBlock(Vector2 pos, bool activate = true);

	bool Load(wstring filePath);

	vector<BlockData> GetBlockDatas();
	vector<ColliderData> GetBlockColliderDatas();
	vector<ColliderData> GetFloorColliderDatas();
	vector<shared_ptr<Transform>> GetTransforms() { return _transforms; }
	vector<InstanceData>& GetInstanceDatas() { return _instanceDatas; }
	shared_ptr<VertexBuffer> GetInstanceBuffer() { return _instanceBuffer; }
	Vector2 GetSize() { return _size; }
	Vector2 GetOutPos() { return _outPos; }
	Vector2 GetMaxFrame() { return _maxFrame; }
	Vector2 GetCurFrame() { return _curFrame; }
	Vector2 GetLeftBottom() { return _leftBottom; }
	Vector2 GetRightTop() { return _rightTop; }
	Vector2 GetPlayerSpawn() { return _playerSpawn; }
	Vector2 GetBossSpawn() { return _bossSpawn; }
	vector<Vector2> GetMonsterSpawn() { return _monsterSpawn; }

	void SetBlockeType(Vector2 curFrame) { _curFrame = curFrame; }
	
	int GetBlockPoolCount() { return _blockPoolCount; }
	int GetBlockIndex();
	bool CheckOverlap(Vector2 pos);
	bool CheckActive(int index);

private:
	void CreateBlocks();

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
	Vector2 _rightTop = { 0, INT_MIN };

	Vector2 _playerSpawn = _outPos;
	Vector2 _bossSpawn = _outPos * 15;

	vector<shared_ptr<RectCollider>> _blocks;
	vector<shared_ptr<RectCollider>> _floors;

	weak_ptr<Advanced_Player> _player;

	vector<shared_ptr<MushroomEnt>> _mushroomEnts;
	vector<Vector2> _monsterSpawn;
};

