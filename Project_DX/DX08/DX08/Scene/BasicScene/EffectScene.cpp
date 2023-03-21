#include "framework.h"
#include "EffectScene.h"

EffectScene::EffectScene()
{
	_transform = make_shared<Transform>();

	string fileN = "Sweeping_4x1";
	wstring file = L"Resources/Texture/Effect/Sweeping_4x1.png";
	EFFECT->AddEffect(file, Vector2(4, 1), Vector2(936, 88), 0.1f, Action::LOOP);
	EFFECT->SetParent(fileN, _transform);
}

EffectScene::~EffectScene()
{
}

void EffectScene::Update()
{
	_transform->SetPos(CAMERA->GetWorldMousePos());

	if (KEY_DOWN(VK_LBUTTON))
	{
		EFFECT->PlayAndMove("Sweeping_4x1");
	}
}

void EffectScene::Render()
{
}

void EffectScene::PostRender()
{
	Vector2 temp = _transform->GetWorldPos();
	ImGui::SliderFloat("TransformPos", &temp.x, 0, WIN_WIDTH);
	ImGui::SliderFloat("TransformPos", &temp.y, 0, WIN_WIDTH);
}
