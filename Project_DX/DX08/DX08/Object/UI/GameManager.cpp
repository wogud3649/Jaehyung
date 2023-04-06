#include "framework.h"
#include "GameManager.h"

GameManager* GameManager::_instance = nullptr;
GameManager::GameManager()
{
	_characterUI = make_shared<CharacterUI>();
	_inventory = make_shared<Inventory>();
	_bg = make_shared<Background>();
}

GameManager::~GameManager()
{
}