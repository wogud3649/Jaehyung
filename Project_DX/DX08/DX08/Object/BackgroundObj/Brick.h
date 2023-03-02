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

private:
	void CreateBlocks();
	shared_ptr<Quad> _quad;
	vector<shared_ptr<Transform>> _transforms;
	vector<shared_ptr<RectCollider>> _cols;
	int _blockType = 0;
	int _blockBasicNumber = 2;
	int _blockPairNumber = 100;
	int _blockIndex = 0;
	vector<bool> _activeBlocks = vector<bool>(_blockBasicNumber * _blockPairNumber, false);
	
	vector<InstanceData> _instanceDatas;
	shared_ptr<VertexBuffer> _instanceBuffer;

	Vector2 _outPos = Vector2(-30, -30);

	weak_ptr<Advanced_Player> _player;
};

