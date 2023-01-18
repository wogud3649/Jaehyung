#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_quad = make_shared<Quad>(L"Resource/Texture/SpyFamily2.png");
	_quad->GetTransform()->GetPos() = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f };
	_quad->GetTransform()->GetScale() *= 0.5;

	_quad2 = make_shared<Quad>(L"Resource/Texture/Pochita.png");
	_quad2->GetTransform()->SetParent(_quad->GetTransform());
	_quad2->GetTransform()->MoveX(500);

	XMMATRIX projectM = XMMatrixOrthographicOffCenterLH(0, WIN_WIDTH, 0, WIN_HEIGHT, -1.0f, 1.0f);
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
	if (GetAsyncKeyState('A') & 0x8001)
	{
		_quad->GetTransform()->MoveX(-0.5f);
	}
	if (GetAsyncKeyState('D') & 0x8001)
	{
		_quad->GetTransform()->MoveX(0.5f);
	}
	if (GetAsyncKeyState('W') & 0x8001)
	{
		_quad->GetTransform()->AddScaleX(0.001f);
		_quad->GetTransform()->AddScaleY(0.001f);
	}
	if (GetAsyncKeyState('S') & 0x8001)
	{
		_quad->GetTransform()->AddScaleX(-0.001f);
		_quad->GetTransform()->AddScaleY(-0.001f);
	}
	if (GetAsyncKeyState('P') & 0x8001)
	{
		_quad->GetTransform()->AddAngle(0.001f);
	}
	if (GetAsyncKeyState('O') & 0x8001)
	{
		_quad->GetTransform()->AddAngle(-0.001f);
	}
	_quad->Update();
	_quad2->Update();
}

void TutorialScene::Render()
{
	_quad->Render();
	_quad2->Render();
}