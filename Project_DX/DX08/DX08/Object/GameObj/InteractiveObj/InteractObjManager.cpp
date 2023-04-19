#include "framework.h"
#include "InteractObjManager.h"

InteractObjManager* InteractObjManager::_instance = nullptr;
InteractObjManager::InteractObjManager()
{
	_stageLevel = 1;
	_door = make_shared<Door>();
	_chest = make_shared<Chest>();
}

InteractObjManager::~InteractObjManager()
{
}

void InteractObjManager::SetPlayer(shared_ptr<Advanced_Player> player)
{
	_door->SetPlayer(player);
	_chest->SetPlayer(player);
}

void InteractObjManager::ExtinctChest()
{
	_chest->Extinct();
}