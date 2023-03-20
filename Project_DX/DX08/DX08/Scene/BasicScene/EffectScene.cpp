#include "framework.h"
#include "EffectScene.h"

EffectScene::EffectScene()
{
	_transform = make_shared<Transform>();

	wstring file = L"Resources/Texture/Effect/Sweeping_6x1.png";
	EFFECT->AddEffect(file, Vector2(7, 1), Vector2(1638, 88), 0.1f, Action::LOOP);
}

EffectScene::~EffectScene()
{
}

void EffectScene::Update()
{
	_transform->SetPos(MOUSE_POS);

	if (KEY_DOWN(VK_LBUTTON))
	{
		EFFECT->Play("Sweeping_6x1", MOUSE_POS);
	}
}

void EffectScene::Render()
{
}