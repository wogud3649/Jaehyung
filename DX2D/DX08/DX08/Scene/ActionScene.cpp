#include "framework.h"
#include "ActionScene.h"

ActionScene::ActionScene()
{
	_sprite = make_shared<Sprite>(L"Resource/Texture/zelda.png", Vector2(10.0f, 8.0f));

	_sprite->GetTransform()->GetPos() = CENTER;

	CreateAction();
}

ActionScene::~ActionScene()
{
}

void ActionScene::Update()
{
	_action->Update();
	_sprite->Update();
}

void ActionScene::Render()
{
	_sprite->SetActionClip(_action->GetCurClip());
	_sprite->Render();
}

void ActionScene::PostRender()
{
	ImGui::SliderInt("Check", &_check, 0, 1);
}

void ActionScene::CreateAction()
{
	Vector2 imageSize = _sprite->GetImageSize();

	vector<Action::Clip> clips;
	float w = imageSize.x / 10.0f;
	float h = imageSize.y / 8.0f;
	float y = h * 4;
	
	for (int i = 0; i < 10; i++)
	{
		clips.emplace_back(w * i, y, w, h, SRV_ADD(L"Resource/Texture/zelda.png"));
	}

	_action = make_shared<Action>(clips, "Front_RUN", Action::PINGPONG);
	_action->SetCallBack(std::bind(&ActionScene::SetCheck, this));
}
