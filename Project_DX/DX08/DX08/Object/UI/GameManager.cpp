#include "framework.h"
#include "GameManager.h"

GameManager* GameManager::_instance = nullptr;
GameManager::GameManager()
{
	_inventory = make_shared<Inventory>();
}

GameManager::~GameManager()
{
}