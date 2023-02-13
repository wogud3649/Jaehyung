#include "framework.h"
#include "EffectScene.h"

EffectScene::EffectScene()
{
	wstring file = L"Resource/Texture/Effects/hit_4x2.png";
	_effect = make_shared<Effect>(file, Vector2(4, 2), Vector2(200, 200), 0.05f);
	_effect->Play(CENTER);
	EFFECT->AddEffect(file, Vector2(4, 2), Vector2(200, 200), 0.05f);

	file = L"Resource/Texture/Effects/smoke_4x4.png";
	_effect = make_shared<Effect>(file, Vector2(4, 4), Vector2(200, 200), 0.05f);
	_effect->Play(CENTER);
	EFFECT->AddEffect(file, Vector2(4, 4), Vector2(200, 200), 0.05f);
}

EffectScene::~EffectScene()
{
}

void EffectScene::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		EFFECT->Play("hit_4x2", MOUSE_POS);
		EFFECT->Play("smoke_4x4", MOUSE_POS);
	}

	_effect->Update();
}

void EffectScene::Render()
{
	_effect->Render();
}
