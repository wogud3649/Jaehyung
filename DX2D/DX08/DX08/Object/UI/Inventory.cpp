#include "framework.h"
#include "Inventory.h"

Inventory::Inventory()
{
	_pannel = make_shared<Quad>(L"Resource/Texture/UI/InventoryPanel.png");

	_slotOffset = Vector2(100, 100);

	for (int y = -1; y < 2; y++)
	{
		for (int x = -1; x < 2; x++)
		{
			shared_ptr<Slot> slot = make_shared<Slot>();
			slot->SetPosition(Vector2(_slotOffset.x * x, _slotOffset.y * y));
			slot->SetParent(_pannel->GetTransform());
			_slots.emplace_back(slot);
		}
	}
}

Inventory::~Inventory()
{
}

void Inventory::Update()
{
	_pannel->Update();
	for (auto slot : _slots)
		slot->Update();
}

void Inventory::Render()
{
	_pannel->Render();
	for (auto slot : _slots)
		slot->Render();
}
