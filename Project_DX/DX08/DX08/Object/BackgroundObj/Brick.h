#pragma once
class Brick
{
public:
	struct BlockData
	{
		Vector2 pos;
		Direction sortx;
		Direction sorty;
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
	void SetTarget(shared_ptr<Advanced_Player> player) { _player = player; }

	int SelectBlock(Vector2 pos);

	void Save();
	void Load();

private:
	void CreateBlocks();
	bool CheckOverlap(Vector2 pos);

	shared_ptr<Quad> _quad;
	vector<shared_ptr<Transform>> _transforms;
	vector<shared_ptr<RectCollider>> _cols;
	Vector2 _size;
	int _blockType = 0;
	int _blockMatterType = 3;
	int _blockShapeType = 2;
	int _blockPairNumber = 100;
	int _totalBlocks = _blockMatterType * _blockShapeType * _blockPairNumber;
	int _blockIndex = 0;
	vector<bool> _activeBlocks = vector<bool>(_totalBlocks, false);
	
	vector<InstanceData> _instanceDatas;
	shared_ptr<VertexBuffer> _instanceBuffer;

	Vector2 _outPos = Vector2(-30, -30);

	weak_ptr<Advanced_Player> _player;
};

