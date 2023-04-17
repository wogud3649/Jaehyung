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
	for (auto sprite : _sprites[_selected])
		sprite->Update();
	for (auto action : _actions[_selected])
		action->Update();
}

void InteractObj::Render()
{
	_sprites[_selected][_isActive]->SetActionClip(_actions[_selected][_isActive]->GetCurClip());
	_sprites[_selected][_isActive]->Render();
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
	DeActivate();

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
	_actions[_selected][false]->Reset();
	_sprites[_selected][_isActive]->SetActionClip(_actions[_selected][_isActive]->GetCurClip());
	_actions[_selected][_isActive]->Play();
}

void InteractObj::DeActivate()
{
	if (_isActive == false)
		return;

	_isActive = false;
	_actions[_selected][true]->Stop();
	_sprites[_selected][_isActive]->SetActionClip(_actions[_selected][_isActive]->GetCurClip());
	_actions[_selected][_isActive]->Play();
}