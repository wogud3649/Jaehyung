#include "framework.h"
#include "Background.h"

Background::Background()
{
	_background = make_shared<Quad>(L"Resources/Texture/BackGround/BlueSky.png");

	_background->GetTransform()->SetPos(CENTER);
	_background->GetTransform()->SetScale(Vector2(1.45f, 1.3f));
	_background->Update();
}

Background::~Background()
{
}

void Background::Update()
{
}

void Background::BackgroundRender()
{
	_background->Render();
}