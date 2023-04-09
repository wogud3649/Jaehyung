#include "framework.h"
#include "InteractObjManager.h"

InteractObjManager* InteractObjManager::_instance = nullptr;
InteractObjManager::InteractObjManager()
{
}

InteractObjManager::~InteractObjManager()
{
}

void InteractObjManager::CreateRandomDoor()
{
	_door = make_shared<Door>();
}

void InteractObjManager::CreateRandomChest()
{
	_chest = make_shared<Chest>();
}

void InteractObjManager::SetPlayer(shared_ptr<Advanced_Player> player)
{
	_door->SetPlayer(player);
	_chest->SetPlayer(player);
}

void InteractObjManager::SpawnDoor()
{
	_door->Spawn();
}

void InteractObjManager::ExtinctDoor()
{
	_door->DeActivate();
	_door->Extinct();
}

void InteractObjManager::ActivateDoor()
{
	_door->Activate();
}

void InteractObjManager::SpawnChest()
{
	_chest->Spawn();
}

void InteractObjManager::ExtinctChest()
{
	_chest->DeActivate();
	_chest->Extinct();
}