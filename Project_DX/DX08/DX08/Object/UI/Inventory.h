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

	void TakeItem(int itemCode);

private:
	void CreateSlots();
	void InstancingIcons();

	shared_ptr<Quad> _inventory;
	shared_ptr<Quad> _extraInventory;
	shared_ptr<Sprite> _inventoryPannels;

	vector<shared_ptr<Slot>> _slots;
	UINT _maxSlot = 43;
	int _selected = -1;

	vector<ItemInfo> _itemDatas;
	shared_ptr<Quad> _itemIcons;
	shared_ptr<Sprite> _itemInfoIcons;
	Vector2 _maxFrame = Vector2(4, 40);
	UINT _itemIconPoolCount = 43;
	vector<InstanceData> _instanceDatas;
	shared_ptr<VertexBuffer> _instanceBuffer;

	Pannel _curPannel = Pannel::EMPTY;
	bool _activeExtraInventory = false;
};

