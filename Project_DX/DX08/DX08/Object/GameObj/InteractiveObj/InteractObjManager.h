#pragma once
class InteractObjManager
{
private:
	InteractObjManager();
	~InteractObjManager();

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new InteractObjManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static InteractObjManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	void SetPlayer(shared_ptr<Advanced_Player> player);

	void ExtinctChest();

	const shared_ptr<Door>& GetDoor() { return _door; }
	const shared_ptr<Chest>& GetChest() { return _chest; }

	const UINT& GetStageLevel() { return _stageLevel; }
	void AddStageLevel() { _stageLevel++; }

private:
	static InteractObjManager* _instance;

	UINT _stageLevel = 1;

	shared_ptr<Door> _door;
	shared_ptr<Chest> _chest;

	bool _doorActive = false;
};