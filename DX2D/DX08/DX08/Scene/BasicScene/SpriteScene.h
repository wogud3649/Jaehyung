#pragma once
class SpriteScene : public Scene
{
public:
	struct InstanceData
	{
		XMMATRIX matrix;
		Vector2 maxFrame;
		Vector2 curFrame;
	};

	SpriteScene();
	~SpriteScene();
	
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
private:
	shared_ptr<Quad> _quad;
	vector<InstanceData> _instanceDatas;
	shared_ptr<VertexBuffer> _instanceBuffer;

	vector<shared_ptr<Sprite>> _sprites;

	// 최적화
	// - 프레임 드랍이 일어나는 이유
	// - GPU한테 DrawCall을 많이 날려서

	// 1. 프러스텀 컬링
	// 2. 오클리전 컬링

	// Instancing
	// -> Vertex Buffer 이용
};

