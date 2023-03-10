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

	_icon = make_shared<ItemIcon>();

	_itemDatas.resize(9);

	_itemDatas[0] = DATA_M->GetItemByName("Sword");
	_itemDatas[1] = DATA_M->GetItemByName("Shoes");
}

Inventory::~Inventory()
{
}

void Inventory::Update()
{
	_icon->SetPos(_slots[0]->GetTransform()->GetWorldPos());
	_icon->SetItem(Vector2(2, 0));

	_pannel->Update();
	_icon->Update();
	for (auto slot : _slots)
		slot->Update();
}

void Inventory::Render()
{
	_pannel->Render();
	for (auto slot : _slots)
		slot->Render();
	_icon->Render();
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
