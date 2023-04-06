#include "framework.h"
#include "Background.h"

Background::Background()
{
	_background = make_shared<Quad>(L"Resources/Texture/BackGround/BlueSky.png");
	_backgroundSize = _background->GetSize();

	_background->GetTransform()->SetPos(CENTER);

}

Background::~Background()
{
}

void Background::Update()
{
	_background->Update();
}

void Background::BackgroundRender()
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
