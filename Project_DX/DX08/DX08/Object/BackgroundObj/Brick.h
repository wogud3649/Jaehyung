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

private:
	shared_ptr<Quad> _quad;
	vector<InstanceData> _instanceDatas;
	shared_ptr<VertexBuffer> _instanceBuffer;

	shared_ptr<Transform> _transform;

	shared_ptr<Action> _pieces;
};

