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

	// ����ȭ
	// - ������ ����� �Ͼ�� ����
	// - GPU���� DrawCall�� ���� ������

	// 1. �������� �ø�
	// 2. ��Ŭ���� �ø�

	// Instancing
	// -> Vertex Buffer �̿�
};

