#pragma once
class Brick
{
public:
	struct BlockData
	{
		int index;
		Vector2 pos;
	};
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

	void Draw(Vector2 pos);
	void Erase(Vector2 pos);
	void Drag(int index, Vector2 pos);
	void SetSpawnPoint(Vector2 pos);

	int SelectBlock(Vector2 pos);

	void Save();
	void Load();

	Vector2 GetPlayerPos() { return _playerSpawnPos; }
	Vector2 GetSize() { return _size; }

private:
	void CreateBlocks();
	bool CheckOverlap(Vector2 pos);

	shared_ptr<Quad> _quad;
	vector<shared_ptr<Transform>> _transforms;
	Vector2 _size;
	int _blockType = 0;
	int _blockShapeType = 2;
	int _blockPairNumber = 90;
	int _totalBlocks = _blockShapeType * _blockPairNumber;
	int _blockIndex = 0;
	vector<bool> _activeBlocks = vector<bool>(_totalBlocks, false);
	
	vector<InstanceData> _instanceDatas;
	shared_ptr<VertexBuffer> _instanceBuffer;

	Vector2 _outPos = Vector2(-50, -50);

	Vector2 _playerSpawnPos;
	shared_ptr<Quad> _spawnPoint;
};

