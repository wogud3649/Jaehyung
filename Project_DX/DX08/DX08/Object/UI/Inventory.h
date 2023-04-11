#pragma once
class Inventory
{
public:
	struct InstanceData
	{
		XMMATRIX matrix;
		Vector2 maxFrame;
		Vector2 curFrame;
	};

	enum Pannel
	{
		EMPTY,
		SINGLE_SKUL_SLOT_SHORT,
		SINGLE_SKUL_SLOT_LONG,
		DOUBLE_SKUL_SLOT_SHORT,
		DOUBLE_SKUL_SLOT_LONG,
		DOUBLE_ITEM_SLOT_SHORT,
		DOUBLE_ITEM_SLOT_LONG,
		ORB_SLOT,
		STATUS
	};

	Inventory();
	~Inventory();

	void Update();
	void PostRender();

	void SetPlayer(shared_ptr<Advanced_Player> player);

	void SellItem(int index);
	void BuyItem(int itemCode, int price);
	bool RootItem(int itemCode);

	vector<ItemInfo> GetEquipedSkulInfo();
	vector<ItemInfo> GetEquipedItemInfo();
	StatAttributes GetEquipStats();
	const UINT& GetMoney() { return _money; }
	const UINT& GetBoneFrag() { return _boneFrag; }

	bool IsOpen() { return _inventoryOpen; }

private:
	void CreateSlots();
	void InstancingIcons();

	void SetInfoPannels();
	void EquipItem(int index);
	void TakeOffItem(int index);
	void RemoveItem(int index);

	shared_ptr<Quad> _inventory;
	shared_ptr<Quad> _extraInventory;
	shared_ptr<Sprite> _inventoryPannels;

	vector<shared_ptr<Slot>> _slots;
	UINT _maxSlot = 43;
	int _curSelected = -1;
	int _oldSelected = _curSelected;
	bool _detailedInfo = false;
	bool _statusOpen = false;

	vector<ItemInfo> _itemDatas;
	shared_ptr<Quad> _itemIcons;
	shared_ptr<Sprite> _itemInfoIcons;
	Vector2 _maxFrame = Vector2(10, 3);
	UINT _itemIconPoolCount = 43;
	vector<InstanceData> _instanceDatas;
	shared_ptr<VertexBuffer> _instanceBuffer;

	Pannel _curPannel = Pannel::EMPTY;
	bool _activeExtraInventory = false;

	UINT _boneFrag = 0;
	UINT _money = 0;

	bool _inventoryOpen = false;

	weak_ptr<Advanced_Player> _player;
};