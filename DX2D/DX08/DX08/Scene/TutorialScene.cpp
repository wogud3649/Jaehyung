#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_quad = make_shared<Quad>(L"Resource/Texture/Chaewon.png");
	_quad->GetTransform()->GetPos() = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f };
	_quad->GetTransform()->GetScale() *= 0.5;

	_quad->SetPS(ADD_PS(L"Shader/FilterPixelShader.hlsl"));

	_reverseBuffer = make_shared<ReverseBuffer>();

	_filterBuffer = make_shared<FilterBuffer>();
	_filterBuffer->_data.value1 = 300;
	_filterBuffer->_data.selected = 0;
	_filterBuffer->_data.imageSize = _quad->GetImageSize();
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
	_reverseBuffer->Update();
	_filterBuffer->Update();
	_quad->Update();
}

void TutorialScene::Render()
{
	_reverseBuffer->SetPSBuffer(0);
	_filterBuffer->SetPSBuffer(1);
	_quad->Render();
}

void TutorialScene::PostRender()
{
	ImGui::SliderInt("Selected", &_filterBuffer->_data.selected, 0, 5);
	ImGui::SliderInt("Value1", &_filterBuffer->_data.value1, 0, 100);
	ImGui::SliderInt("Value2", &_filterBuffer->_data.value2, 0, 100);
}
