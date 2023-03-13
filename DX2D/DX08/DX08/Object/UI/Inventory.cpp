#include "framework.h"
#include "Inventory.h"

Inventory::Inventory()
{
	_pannel = make_shared<Quad>(L"Resource/Texture/UI/InventoryPanel.png");

	_slotOffset = Vector2(100, 100);

	for (int y = 1; y > -2; y--)
	{
		for (int x = -1; x < 2; x++)
		{
			shared_ptr<Slot> slot = make_shared<Slot>();
			slot->SetPosition(Vector2(_slotOffset.x * x, _slotOffset.y * y));
			slot->SetParent(_pannel->GetTransform());
			_slots.emplace_back(slot);
		}
	}

	for (int i = 0; i < 0; i++)
	{
		shared_ptr<ItemIcon> icon = make_shared<ItemIcon>();
		_icons.emplace_back(icon);
	}

	_itemDatas.resize(9);

	_itemDatas[0] = DATA_M->GetItemByName("Sword");
	_itemDatas[1] = DATA_M->GetItemByName("Shoes");
}

Inventory::~Inventory()
{
}

void Inventory::Update()
{
	_pannel->Update();
	
	for (auto icon : _icons)
		icon->Update();

	for (auto slot : _slots)
		slot->Update();
}

void Inventory::Render()
{
	_pannel->Render();

	for (auto slot : _slots)
		slot->Render();

	for (auto icon : _icons)
		icon->Render();
}

void Inventory::PostRender()
{
	RECT rect;
	// 750 170... 가로 세로 50, 30
	rect.left = 725;
	rect.right = 775;
	rect.bottom = 155;
	rect.top = 185;

	wstring money = to_wstring(_money);
	DirectWrite::GetInstance()->RenderText(L"Money : " + money, rect, 20.0f);
}

void Inventory::Set()
{
	for (int i = 0; i < _icons.size(); i++)
	{
		_icons[i]->SetPos(_slots[i]->GetTransform()->GetWorldPos());
		_icons[i]->SetItem(_itemDatas[i]);
	}
}

void Inventory::BuyItem(string name)
{
	ItemInfo info = DATA_M->GetItemByName(name);
	
	if (info.name == "" || _money - info.price < 0)
		return;

	auto iter = std::find(_itemDatas.begin(), _itemDatas.end(), [](const ItemInfo& info)->bool
		{
			if (info.name == "")
				return true;
			return false;
		});

	if (iter == _itemDatas.end())
	{
		return;
	}

	*iter = info;
	Set();

	SubMoney(info.price);
}

void Inventory::SellItem(string name)
{
	auto iter = std::find_if(_itemDatas.begin(), _itemDatas.end(), [name](const ItemInfo& info)->bool
		{
			if (info.name == name)
				return true;
			return false;
		});

	if (iter == _itemDatas.end())
		return;

	AddMoney(iter->price);
	iter->SetEmpty();

	Set();
}

bool Inventory::AddMoney(UINT amount)
{
	_money += amount;
	return true;
}

bool Inventory::SubMoney(UINT amount)
{
	if (_money - amount < 0)
		return false;

	_money -= amount;
	return true;
}
