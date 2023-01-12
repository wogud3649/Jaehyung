#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_quad = make_shared<Quad>(L"Resource/Texture/SpyFamily2.png");

	_view = make_shared<MatrixBuffer>();
	_projection = make_shared<MatrixBuffer>();

	XMMATRIX projectM = XMMatrixOrthographicLH(WIN_WIDTH, WIN_HEIGHT, 0.0f, 1.0f);

	_projection->SetData(projectM);
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
	_quad->Update();

	_view->Update();
	_projection->Update();
}

void TutorialScene::Render()
{
	_view->SetVSBuffer(1);
	_projection->SetVSBuffer(2);

	_quad->Render();
}