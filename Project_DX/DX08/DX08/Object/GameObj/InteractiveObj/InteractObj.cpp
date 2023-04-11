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
	_col->Update();
	for (auto sprite : _sprites)
		sprite->Update();
	for (auto action : _actions)
		action->Update();
}

void InteractObj::Render()
{
	_sprites[_isActive]->SetActionClip(_actions[_isActive]->GetCurClip());
	_sprites[_isActive]->Render();
	_col->Render();
}

void InteractObj::CreateAction()
{
}

void InteractObj::Spawn()
{
	if (_isSpawn)
		return;

	_isSpawn = true;
}

void InteractObj::Extinct()
{
	if (_isSpawn == false)
		return;

	_isSpawn = false;
	_col->DeActivate();
}

void InteractObj::Activate()
{
	if (_isActive)
		return;

	_isActive = true;
	_actions[false]->Reset();
	_sprites[_isActive]->SetActionClip(_actions[_isActive]->GetCurClip());
	_actions[_isActive]->Play();
}

void InteractObj::DeActivate()
{
	if (_isActive == false)
		return;

	_isActive = false;
	_actions[true]->Stop();
	_sprites[_isActive]->SetActionClip(_actions[_isActive]->GetCurClip());
	_actions[_isActive]->Play();
}