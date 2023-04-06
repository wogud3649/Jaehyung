#include "framework.h"
#include "InteractObj.h"

InteractObj::InteractObj()
{
}

InteractObj::~InteractObj()
{
}

void InteractObj::Update()
{
	//_col->Update();
	for (auto sprite : _sprites)
		sprite->Update();
	for (auto action : _actions)
		action->Update();
}

void InteractObj::Render()
{
	_sprites[_isActive]->SetActionClip(_actions[_isActive]->GetCurClip());
	_sprites[_isActive]->Render();
	//_col->Render();
}

void InteractObj::CreateAction()
{
}

void InteractObj::SetActive()
{
	_actions[true]->Play();
	_sprites[true]->SetActionClip(_actions[true]->GetCurClip());
	_isActive = true;
}
