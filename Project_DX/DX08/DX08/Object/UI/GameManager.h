#pragma once
class GameManager
{
private:
	GameManager();
	~GameManager();

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new GameManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static GameManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	const shared_ptr<Advanced_Player>& GetPlayer() { return _player; }
	const shared_ptr<Inventory>& GetInventory() { return _inventory; }
	const shared_ptr<Background>& GetBackground() { return _bg; }
	const shared_ptr<Store>& GetStore() { return _store; }
	const shared_ptr<Yggdrasil>& GetYggdrasil() { return _yggdrasil; }
	const shared_ptr<CharacterUI>& GetCharacterUI() { return _characterUI; }

private:
	static GameManager* _instance;

	shared_ptr<Advanced_Player> _player;
	shared_ptr<Inventory> _inventory;
	shared_ptr<Background> _bg;
	shared_ptr<Store> _store;
	shared_ptr<Yggdrasil> _yggdrasil;
	shared_ptr<CharacterUI> _characterUI;
};