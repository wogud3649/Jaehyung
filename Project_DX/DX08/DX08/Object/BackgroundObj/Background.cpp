#include "framework.h"
#include "Background.h"

Background::Background()
{
	_background = make_shared<Quad>(L"Resources/Texture/BackGround/GrayBackground.png");
	Vector2 size = _background->GetSize();
	Vector2 tempPos = Vector2(size.x * 0.5f, -size.y * 0.5f + WIN_HEIGHT);

	_background->GetTransform()->SetPos(tempPos);
	_backgroundSize = size;

}

Background::~Background()
{
}

void Background::Update()
{
	_background->Update();
}

void Background::Render()
{
	_background->Render();
}

Vector2 Background::LeftBottom()
{
	Vector2 curPos = _background->GetTransform()->GetWorldPos();
	Vector2 size = _background->GetSize() * 0.5f;
	return (curPos - size);
}

Vector2 Background::RightTop()
{
	Vector2 curPos = _background->GetTransform()->GetWorldPos();
	Vector2 size = _background->GetSize() * 0.5f;
	return (curPos + size);
}
