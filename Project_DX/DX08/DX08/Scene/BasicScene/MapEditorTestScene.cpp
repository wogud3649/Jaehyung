#include "framework.h"
#include "MapEditorTestScene.h"

MapEditorTestScene::MapEditorTestScene()
{
	_quad = make_shared<Quad>(L"Resources/Texture/Background/Brick.png");
	_quad->SetVS(ADD_VS(L"Shader/InstancingVertexShader.hlsl"));
	_quad->SetPS(ADD_PS(L"Shader/InstancingPixelShader.hlsl"));

	_instanceDatas.resize(300);

	for (auto& data : _instanceDatas)
	{
		Transform transform;
		Vector2 pos = { MathUtility::RandomFloat(0.0f, WIN_WIDTH), MathUtility::RandomFloat(0.0f, WIN_HEIGHT) };
		float scaleX = MathUtility::RandomFloat(0.1f, 1.0f);

		transform.SetPos(pos);
		transform.SetScale({ scaleX, scaleX });
		transform.UpdateSRT();

		data.maxFrame = Vector2(4.0f, 4.0f);
		data.curFrame = Vector2(MathUtility::RandomInt(0, 4), MathUtility::RandomInt(0, 4));

		data.matrix = XMMatrixTranspose(transform.GetMatrix());
	}

	_transform = make_shared<Transform>();
	_transform->SetPos(CENTER);
	_transform->SetScale({ 0.5f,0.5f });
	_transform->UpdateSRT();

	_instanceDatas[0].matrix = XMMatrixTranspose(_transform->GetMatrix());

	_instanceBuffer = make_shared<VertexBuffer>(_instanceDatas.data(), sizeof(InstanceData), _instanceDatas.size(), 0, true);
}

MapEditorTestScene::~MapEditorTestScene()
{
}

void MapEditorTestScene::Init()
{
}

void MapEditorTestScene::Fin()
{
}

void MapEditorTestScene::Update()
{
	//_instanceBuffer->Update();
}

void MapEditorTestScene::Render()
{
	_instanceBuffer->IASet(1);

	_quad->SetRender();

	DC->DrawIndexedInstanced(6, _instanceDatas.size(), 0, 0, 0);
}

void MapEditorTestScene::PreRender()
{
}

void MapEditorTestScene::PostRender()
{
}
