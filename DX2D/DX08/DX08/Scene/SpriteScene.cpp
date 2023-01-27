#include "framework.h"
#include "SpriteScene.h"

SpriteScene::SpriteScene()
{
	_sprite = make_shared<Sprite>(L"Resource/Texture/zelda.png", Vector2(10.0f,8.0f));

	_sprite->GetTransform()->GetPos() = CENTER;
}

SpriteScene::~SpriteScene()
{
}

void SpriteScene::Update()
{
	_sprite->Update();

	_sprite->SetCurFrame(Vector2(curFrameX, curFrameY));

	if (KEY_PRESS('D'))
	{
		_sprite->GetTransform()->GetPos().x += DELTA_TIME * 50.0f;
	}
}

void SpriteScene::Render()
{
	_sprite->Render();
}

void SpriteScene::PostRender()
{
	ImGui::SliderInt("CurFrameX", &curFrameX, 0, 10);
	ImGui::SliderInt("CurFrameY", &curFrameY, 0, 8);
}
