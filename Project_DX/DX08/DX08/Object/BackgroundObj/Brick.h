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

	void SetPlayer(shared_ptr<Advanced_Player> player) { _player = player; }

	void Draw(Vector2 pos);
	void Erase(Vector2 pos);
	void Drag(int index, Vector2 pos);

	void SetBlockCollider(Vector2 start, Vector2 end);
	void SetFloorCollider(Vector2 start, Vector2 end);
	void DeleteBlockCollider();
	void DeleteFloorCollider();

	int SelectBlock(Vector2 pos);

	void Load();

	vector<BlockData> GetBlockDatas();
	vector<ColliderData> GetBlockColliderDatas();
	vector<ColliderData> GetFloorColliderDatas();
	Vector2 GetSize() { return _size; }
	Vector2 GetLeftBottom() { return _leftBottom; }
	Vector2 GetRightTop() { return _rightTop; }
	Vector2 GetPlayerSpawn() { return _playerSpawn; }

private:
	void CreateBlocks();
	bool CheckOverlap(Vector2 pos);

	shared_ptr<Quad> _quad;
	vector<shared_ptr<Transform>> _transforms;
	Vector2 _size;
	int _blockType = 0;
	int _blockShapeType = 2;
	int _blockPairNumber = 150;
	int _totalBlocks = _blockShapeType * _blockPairNumber;
	int _blockIndex = 0;
	vector<bool> _activeBlocks = vector<bool>(_totalBlocks, false);
	
	vector<InstanceData> _instanceDatas;
	shared_ptr<VertexBuffer> _instanceBuffer;

	Vector2 _outPos = Vector2(-30, -30);
	Vector2 _leftBottom = { INT_MAX, INT_MAX };
	Vector2 _rightTop = { 0, INT_MIN };

	Vector2 _playerSpawn = _outPos;

	vector<shared_ptr<RectCollider>> _blocks;
	vector<shared_ptr<RectCollider>> _floors;

	weak_ptr<Advanced_Player> _player;
};

