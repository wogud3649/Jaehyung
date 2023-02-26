#pragma once
class MapEditorTestScene : public Scene
{
public:
	struct InstanceData
	{
		XMMATRIX matrix;
		Vector2 maxFrame;
		Vector2 curFrame;
	};

	MapEditorTestScene();
	virtual ~MapEditorTestScene();

	virtual void Init() override;
	virtual void Fin() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void PostRender() override;

private:
	shared_ptr<Quad> _quad;
	vector<InstanceData> _instanceDatas;
	shared_ptr<VertexBuffer> _instanceBuffer;

	shared_ptr<Transform> _transform;
};

