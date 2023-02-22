#include "framework.h"
#include "SpriteScene.h"

SpriteScene::SpriteScene()
{
	_quad = make_shared<Quad>(L"Resource/Texture/zelda.png");
	_quad->SetVS(ADD_VS(L"Shader/InstancingVertexShader.hlsl"));
	_quad->SetPS(ADD_PS(L"Shader/InstancingPixelShader.hlsl"));

	_instanceDatas.resize(300);

	for (auto& data : _instanceDatas)
	{
		Transform transform;
		Vector2 pos = { MathUtility::RandomFloat(0.0f,WIN_WIDTH), MathUtility::RandomFloat(0.0f, WIN_HEIGHT) };
		float scaleX = MathUtility::RandomFloat(0.01f, 0.1f);

		transform.SetPosition(pos);
		transform.GetScale() = Vector2(scaleX, scaleX);
		transform.UpdateSRT();

		data.maxFrame = Vector2(10.0f, 8.0f);
		data.curFrame = Vector2(MathUtility::RandomInt(0, 10), MathUtility::RandomInt(0, 8));

		data.matrix = XMMatrixTranspose(transform.GetMatrix());
	}

	_instanceBuffer = make_shared<VertexBuffer>(_instanceDatas.data(), sizeof(InstanceData), _instanceDatas.size(), 0, true);
	_instanceBuffer->Update();
}

SpriteScene::~SpriteScene()
{
}

void SpriteScene::Update()
{
}

void SpriteScene::Render()
{
	_instanceBuffer->IASet(1);

	_quad->SetRender();

	DC->DrawIndexedInstanced(6, _instanceDatas.size(), 0, 0, 0);
}

void SpriteScene::PostRender()
{
}
