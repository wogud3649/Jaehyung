#include "TutorialScene.h"
#include "framework.h"

TutorialScene::TutorialScene()
{
	_vertexBuffer = make_shared<VertexBuffer>();
	
	_vs = make_shared<VertexShader>(L"Shader/TutorialShader.hlsl");
	_ps = make_shared<PixelShader>(L"Shader/TutorialShader.hlsl");
	_srv = make_shared<SRV>(L"Resource/Texture/Pochita.png");
	_sampler = make_shared<SamplerState>();
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{

}

void TutorialScene::Render()
{
	_vertexBuffer->Set(0);

	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	_srv->Set(0);
	_sampler->Set(0);

	_vs->Set();
	_ps->Set();

	DC->Draw(6, 0);
}
