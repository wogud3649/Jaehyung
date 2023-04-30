#pragma once
class DataManager
{
private:
	DataManager();
	~DataManager();

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new DataManager();
	}

	static  void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static DataManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
		return nullptr;
	}

	void LoadItemInfo();
	void SetDuplicate(UINT itemCode) { _checkDuplicate[itemCode] = true; }

	const ItemInfo& GetItemByItemCode(int itemCode);
	const unordered_map<int, ItemInfo>& GetItemTable() { return _itemTable; }
	//const bool& CheckDuplicate(UINT itemCode) { return _checkDuplicate[itemCode]; }

private:
	static DataManager* _instance;

	unordered_map<int, ItemInfo> _itemTable;
	shared_ptr<tinyxml2::XMLDocument> _document;

	unordered_map<UINT, bool> _checkDuplicate;
};