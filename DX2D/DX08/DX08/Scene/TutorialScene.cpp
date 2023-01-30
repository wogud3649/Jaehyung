#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_quad = make_shared<Quad>(L"Resource/Texture/SpyFamily2.png");
	_quad->GetTransform()->GetPos() = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f };
	_quad->GetTransform()->GetScale() *= 0.5;

	_quad->SetPS(ADD_PS(L"Shader/LRTexturePixelShader.hlsl"));

	_reverseBuffer = make_shared<ReverseBuffer>();
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
	_reverseBuffer->Update();
	_quad->Update();
}

void TutorialScene::Render()
{
	_reverseBuffer->SetPSBuffer(0);
	_quad->Render();
}

void TutorialScene::PostRender()
{
	if (ImGui::Button("Reverse1", { 100,100 }))
	{
		_reverseBuffer->_data.reverse = 1;
	}
	if (ImGui::Button("Reverse0", { 100,100 }))
	{
		_reverseBuffer->_data.reverse = 0;
	}
}
