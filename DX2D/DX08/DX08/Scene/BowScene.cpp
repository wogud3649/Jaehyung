#include "framework.h"
#include "BowScene.h"

BowScene::BowScene()
{
	_bow = make_shared<Bow>(L"Resource/Texture/Bow.png");
	_bow->SetPos(Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f));

	_arrow = make_shared<Bow>(L"Resource/Texture/Bullet.png");
	_arrow->SetParent(_bow->GetVirtualTransform());
	_arrow->SetScale(Vector2(0.5f, 0.5f));

}

BowScene::~BowScene()
{
}

void BowScene::Update()
{
	if (GetAsyncKeyState('W') & 0x8001)
	{
		_bow->GetTransform()->GetAngle() += 0.0005;
	}
	if (GetAsyncKeyState('S') & 0x8001)
	{
		_bow->GetTransform()->GetAngle() -= 0.0005;
	}
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		_arrow->GetTransform()->GetPos().x += 0.05;
	}
	if (Get)
	_bow->GetVirtualTransform()->GetAngle() = _bow->GetTransform()->GetAngle();
	_bow->Update();
	_arrow->Update();
}

void BowScene::Render()
{
	_bow->Render();
	_arrow->Render();
}
