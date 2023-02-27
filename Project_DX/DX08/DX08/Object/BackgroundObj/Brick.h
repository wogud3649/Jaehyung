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

	void Createblocks();
private:
	vector<shared_ptr<Quad>> _quads;
	vector<InstanceData> _instanceDatas;
	shared_ptr<VertexBuffer> _instanceBuffer;

	shared_ptr<Transform> _transform;
};

