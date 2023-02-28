#pragma once
class Brick
{
public:
	enum Direction
	{
		LEFT,
		TOP,
		MID,
		RIGHT,
		BOTTOM
	};
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

private:
	shared_ptr<Quad> _quad;
	vector<shared_ptr<RectCollider>> _cols;
	
	vector<InstanceData> _instanceDatas;
	shared_ptr<VertexBuffer> _instanceBuffer;

	vector<BlockData> _blockDatas;
	int _blockIndex = 0;

	shared_ptr<Transform> _transform;
};

