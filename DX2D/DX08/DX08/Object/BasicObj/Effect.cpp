#include "framework.h"
#include "Effect.h"

Effect::Effect(wstring file, Vector2 maxFrame, Vector2 size, float speed, Action::Type type)
{
	CreateAction(file, maxFrame, size, speed, type);
}

Effect::~Effect()
{
}

void Effect::Update()
{
	if (_isActive == false) return;

	_sprite->Update();
	_action->Update();
}

void Effect::Render()
{
	if (_isActive == false) return;

	_sprite->SetActionClip(_action->GetCurClip());
	_sprite->Render();
}

void Effect::PostRender()
{
}

void Effect::Play(Vector2 pos)
{
	_isActive = true;
	_action->Play();
	_sprite->GetTransform()->SetPosition(pos);
}

void Effect::End()
{
	_isActive = false;
	_action->Reset();
}

void Effect::SetActive(bool active)
{
	_isActive = active;
	_action->Reset();
}

void Effect::CreateAction(wstring file, Vector2 maxFrame, Vector2 size, float speed, Action::Type type)
{
	_sprite = make_shared<Sprite>(file, maxFrame, size);

	Vector2 clipSize = _sprite->GetImageSize();
	clipSize.x /= maxFrame.x;
	clipSize.y /= maxFrame.y;

	vector<Action::Clip> clips;
	
	for (int y = 0; y < maxFrame.y; y++)
	{
		for (int x = 0; x < maxFrame.x; x++)
		{
			clips.emplace_back(x * clipSize.x, y * clipSize.y, clipSize.x, clipSize.y, SRV_ADD(file));
		}
	}

	string name = string(file.begin(), file.end());
	name = name.substr(name.find_last_of("/") + 1);
	name = name.substr(0, name.find_last_of("."));

	_action = make_shared<Action>(clips, name, type, speed);
	_action->SetCallBack(std::bind(&Effect::End, this));
}
