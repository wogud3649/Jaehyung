#include "framework.h"
#include "GameManager.h"

GameManager* GameManager::_instance = nullptr;
GameManager::GameManager()
{
	_player = make_shared<Advanced_Player>();
	_inventory = make_shared<Inventory>();
	_bg = make_shared<Background>();
	_store = make_shared<Store>();
	_yggdrasil = make_shared<Yggdrasil>();
	_characterUI = make_shared<CharacterUI>();
	_fadePanel = make_shared<FadePanel>();
}

GameManager::~GameManager()
{
}