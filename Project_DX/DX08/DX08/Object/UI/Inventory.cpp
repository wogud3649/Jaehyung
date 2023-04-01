#include "framework.h"
#include "Inventory.h"

Inventory::Inventory()
{
	_inventory = make_shared<Quad>(L"Resources/Texture/UI/InventoryPannel.png");
	_inventory->GetTransform()->SetPos(CENTER);

	_extraInventory = make_shared<Quad>(L"Resources/Texture/UI/ExtraItemSlot.png");
	_extraInventory->GetTransform()->SetParent(_inventory->GetTransform());

	_inventoryPannels = make_shared<Sprite>(L"Resources/Texture/UI/InventoryPannels.png", Vector2(3,3), Vector2(3840, 2121));
	_inventoryPannels->GetTransform()->SetParent(_inventory->GetTransform());
	_inventoryPannels->GetTransform()->MoveX(-1);
	_inventoryPannels->SetCurFrame(Vector2(2, 2));

	_itemDatas.resize(43);

	_itemInfoIcons = make_shared<Sprite>(L"Resources/Texture/Item/ItemInfoIcons_10x3.png", Vector2(10, 3), Vector2(3300, 1560));
	_itemInfoIcons->GetTransform()->SetPos(Vector2(867, 626));
	_itemInfoIcons->SetCurFrame(Vector2(0, 0));

	CreateSlots();
	RootItem(-1);
	RootItem(23);
	RootItem(23);
	RootItem(23);
	RootItem(23);
	RootItem(23);
	RootItem(23);
	RootItem(23);
	RootItem(23);
	RootItem(23);
	RootItem(22);
	RootItem(1);
	RootItem(2);
	RootItem(19);
	RootItem(19);
}

Inventory::~Inventory()
{
}

void Inventory::Update()
{
	if (KEY_DOWN('I'))
		_inventoryOpen = !_inventoryOpen;

	if (_inventoryOpen == false)
		return;

	_inventory->Update();
	_inventoryPannels->Update();
	_itemInfoIcons->Update();
	
	if (KEY_DOWN('A'))
		_activeExtraInventory = !_activeExtraInventory;

	if (KEY_DOWN(VK_RBUTTON))
	{
		_itemInfoIcons->SetCurFrame(Vector2(2, 8));
	}
	if (KEY_UP(VK_RBUTTON))
	{
		_itemInfoIcons->SetCurFrame(Vector2(0, 0));
	}

	if (KEY_DOWN(VK_RBUTTON))
	{
		_curPannel = static_cast<Pannel>(_curPannel + 1);
		if (_curPannel > Pannel::STATUS)
			_curPannel = Pannel::EMPTY;

		switch (_curPannel)
		{
		case Inventory::EMPTY:
			_inventoryPannels->SetCurFrame(Vector2(2, 2));
			break;
		case Inventory::SINGLE_SKUL_SLOT_SHORT:
			_inventoryPannels->SetCurFrame(Vector2(3, 3));
			break;
		case Inventory::SINGLE_SKUL_SLOT_LONG:
			_inventoryPannels->SetCurFrame(Vector2(1, 3));
			break;
		case Inventory::DOUBLE_SKUL_SLOT_SHORT:
			_inventoryPannels->SetCurFrame(Vector2(2, 3));
			break;
		case Inventory::DOUBLE_SKUL_SLOT_LONG:
			_inventoryPannels->SetCurFrame(Vector2(3, 1));
			break;
		case Inventory::DOUBLE_ITEM_SLOT_SHORT:
			_inventoryPannels->SetCurFrame(Vector2(1, 1));
			break;
		case Inventory::DOUBLE_ITEM_SLOT_LONG:
			_inventoryPannels->SetCurFrame(Vector2(2, 1));
			break;
		case Inventory::ORB_SLOT:
			_inventoryPannels->SetCurFrame(Vector2(3, 2));
			break;
		case Inventory::STATUS:
			_inventoryPannels->SetCurFrame(Vector2(1, 2));
			break;
		default:
			break;
		}
	}

	if (_activeExtraInventory)
	{
		_extraInventory->Update();

		for (int i = 16; i < _maxSlot; i++)
		{
			_slots[i]->Update();
			if (_slots[i]->IsCollision(MOUSE_POS))
			{
				_selected = i;
				if (KEY_DOWN(VK_LBUTTON))
					EquipItem(i);
			}
		}
	}
	else
	{
		for (int i = 0; i < 16; i++)
		{
			_slots[i]->Update();
			if (_slots[i]->IsCollision(MOUSE_POS))
			{
				_selected = i;
				if (KEY_DOWN(VK_LBUTTON))
					TakeOffItem(i);
			}
		}
	}

	if (_selected != -1)
	{
		ItemInfo itemCode = _itemDatas[_selected];
		_itemInfoIcons->SetCurFrame(Vector2(itemCode.frameX, itemCode.frameY));
	}
}

void Inventory::PostRender()
{
	if (_inventoryOpen == false)
		return;

	ImGui::SliderInt("Selected", &_selected, -1, 43);
	_inventory->Render();
	_inventoryPannels->Render();
	_itemInfoIcons->Render();
	
	if (_activeExtraInventory)
	{
		_extraInventory->Render();
		_instanceBuffer->IASet(1);
		_itemIcons->SetRender();
		DC->DrawIndexedInstanced(6, 27, 0, 0, 16);

		for (int i = 16; i < _maxSlot; i++)
		{
			_slots[i]->Render();
		}
	}
	else
	{
		_instanceBuffer->IASet(1);
		_itemIcons->SetRender();
		DC->DrawIndexedInstanced(6, 16, 0, 0, 0);
		for (int i = 0; i < 16; i++)
		{
			_slots[i]->Render();
		}
	}
}

void Inventory::SetPlayer(shared_ptr<Advanced_Player> player)
{
	_player = player;
	if (_player.expired() == false)
		_player.lock()->SetEquipStats(this->GetEquipStats());
}

void Inventory::EquipItem(int index)
{
	if (index == -1)
		return;

	ItemInfo info = _itemDatas[index];
	if (info.itemCode == 0)
		return;

	bool success = false;

	switch (info.itemType)
	{
	case ItemType::HEAD:
		for (int i = 0; i < 2; i++)
		{
			if (_itemDatas[i].itemCode == 0)
			{
				_itemDatas[i] = info;
				_instanceDatas[i].curFrame = { info.frameX, info.frameY };
				_instanceBuffer->Update();
				success = true;
				break;
			}
		}
		break;
	case ItemType::EQUIPMENT:
		for (int i = 3; i < 12; i++)
		{
			if (_itemDatas[i].itemCode == 0)
			{
				_itemDatas[i] = info;
				_instanceDatas[i].curFrame = { info.frameX, info.frameY };
				_instanceBuffer->Update();
				success = true;
				break;
			}
		}
		break;
	default:
		break;
	}
	
	if (success)
	{
		if (_player.expired() == false)
			_player.lock()->SetEquipStats(this->GetEquipStats());

		_itemDatas[index].SetEmpty();
		_instanceDatas[index].curFrame = Vector2(0, 0);
		_instanceBuffer->Update();
	}
}

void Inventory::TakeOffItem(int index)
{
	if (index == -1)
		return;

	ItemInfo info = _itemDatas[index];
	if (info.itemCode == 0)
		return;

	bool success = false;
	for (int i = 16; i < _itemIconPoolCount; i++)
	{
		if (_itemDatas[i].itemCode == 0)
		{
			_itemDatas[i] = info;
			_instanceDatas[i].curFrame = { info.frameX, info.frameY };
			success = true;
			break;
		}
	}

	if (success)
		RemoveItem(index);
}

void Inventory::RemoveItem(int index)
{
	_itemDatas[index].SetEmpty();
	_instanceDatas[index].curFrame = Vector2(0, 0);
	_instanceBuffer->Update();

	if (_player.expired() == false)
		_player.lock()->SetEquipStats(this->GetEquipStats());
}

void Inventory::SellItem(int index)
{
	if (index == -1)
		return;

	ItemInfo info = _itemDatas[index];
	if (info.itemCode == 0)
		return;

	if (info.itemType == ItemType::HEAD)
		_boneFrag += info.price;
	else
		_money += info.price;

	RemoveItem(index);
}

void Inventory::BuyItem(int itemCode, int price)
{
	if (price < 0)
		return;
	if (itemCode == 0)
		return;
	if (_money < price)
		return;

	bool success = RootItem(itemCode);
	if (success)
		_money -= price;
}

bool Inventory::RootItem(int itemCode)
{
	ItemInfo info = DATA_M->GetItemByItemCode(itemCode);
	if (info.itemCode == 0)
		return false;

	bool success = false;
	switch (info.itemType)
	{
	case ItemType::HEAD:
		for (int i = 0; i < 2; i++)
		{
			if (_itemDatas[i].itemCode == 0)
			{
				_itemDatas[i] = info;
				_instanceDatas[i].curFrame = { info.frameX, info.frameY };
				success = true;
				break;
			}
		}
		break;
	case ItemType::EQUIPMENT:
		for (int i = 3; i < 12; i++)
		{
			if (_itemDatas[i].itemCode == 0)
			{
				_itemDatas[i] = info;
				_instanceDatas[i].curFrame = { info.frameX, info.frameY };
				success = true;
				break;
			}
		}
		break;
	default:
		break;
	}

	if (success == false)
	{
		for (int i = 16; i < _itemIconPoolCount; i++)
		{
			if (_itemDatas[i].itemCode == 0)
			{
				_itemDatas[i] = info;
				_instanceDatas[i].curFrame = { info.frameX, info.frameY };
				success = true;
				break;
			}
		}
	}

	if (success == false)
		return false;

	if (_player.expired() == false)
		_player.lock()->SetEquipStats(this->GetEquipStats());
	
	_instanceBuffer->Update();
	return true;
}

vector<ItemInfo> Inventory::GetEquipedSkulInfo()
{
	vector<ItemInfo> data;
	
	for (int i = 0; i < 2; i++)
	{
		if (_itemDatas[i].itemCode == 0)
			data.emplace_back(ItemInfo());
		else
			data.emplace_back(_itemDatas[i]);
	}

	return data;
}

vector<ItemInfo> Inventory::GetEquipedItemInfo()
{
	vector<ItemInfo> data;

	for (int i = 3; i < 12; i++)
	{
		if (_itemDatas[i].itemCode == 0)
			data.emplace_back(ItemInfo());
		else
			data.emplace_back(_itemDatas[i]);
	}

	return data;
}

StatAttributes Inventory::GetEquipStats()
{
	StatAttributes stats;

	for (int i = 0; i < 12; i++)
	{
		stats += _itemDatas[i].statAttributes;
	}

	return stats;
}

void Inventory::CreateSlots()
{
	InstancingIcons();

	for (int i = 0; i < _maxSlot; i++)
	{
		shared_ptr<Slot> slot = make_shared<Slot>();
		slot->GetCollider()->GetTransform()->SetParent(_inventory->GetTransform());
		_slots.emplace_back(slot);
	}

	Vector2 movePos = { -284, 236 };
	_slots[0]->GetCollider()->GetTransform()->Move(movePos);
	_instanceDatas[0].matrix = XMMatrixTranspose(_slots[0]->GetCollider()->GetTransform()->GetMatrix());
	movePos.x = -198;
	_slots[1]->GetCollider()->GetTransform()->Move(movePos);
	_instanceDatas[1].matrix = XMMatrixTranspose(_slots[1]->GetCollider()->GetTransform()->GetMatrix());
	movePos = { -241, 130 };
	_slots[2]->GetCollider()->GetTransform()->Move(movePos);
	_instanceDatas[2].matrix = XMMatrixTranspose(_slots[2]->GetCollider()->GetTransform()->GetMatrix());
	movePos = { -327, 24 };
	_slots[3]->GetCollider()->GetTransform()->Move(movePos);
	_instanceDatas[3].matrix = XMMatrixTranspose(_slots[3]->GetCollider()->GetTransform()->GetMatrix());
	movePos.x = -241;
	_slots[4]->GetCollider()->GetTransform()->Move(movePos);
	_instanceDatas[4].matrix = XMMatrixTranspose(_slots[4]->GetCollider()->GetTransform()->GetMatrix());
	movePos.x = -155;
	_slots[5]->GetCollider()->GetTransform()->Move(movePos);
	_instanceDatas[5].matrix = XMMatrixTranspose(_slots[5]->GetCollider()->GetTransform()->GetMatrix());
	movePos = { -327, -41 };
	_slots[6]->GetCollider()->GetTransform()->Move(movePos);
	_instanceDatas[6].matrix = XMMatrixTranspose(_slots[6]->GetCollider()->GetTransform()->GetMatrix());
	movePos.x = -241;
	_slots[7]->GetCollider()->GetTransform()->Move(movePos);
	_instanceDatas[7].matrix = XMMatrixTranspose(_slots[7]->GetCollider()->GetTransform()->GetMatrix());
	movePos.x = -155;
	_slots[8]->GetCollider()->GetTransform()->Move(movePos);
	_instanceDatas[8].matrix = XMMatrixTranspose(_slots[8]->GetCollider()->GetTransform()->GetMatrix());
	movePos = { -327, -106 };
	_slots[9]->GetCollider()->GetTransform()->Move(movePos);
	_instanceDatas[9].matrix = XMMatrixTranspose(_slots[9]->GetCollider()->GetTransform()->GetMatrix());
	movePos.x = -241;
	_slots[10]->GetCollider()->GetTransform()->Move(movePos);
	_instanceDatas[10].matrix = XMMatrixTranspose(_slots[10]->GetCollider()->GetTransform()->GetMatrix());
	movePos.x = -155;
	_slots[11]->GetCollider()->GetTransform()->Move(movePos);
	_instanceDatas[11].matrix = XMMatrixTranspose(_slots[11]->GetCollider()->GetTransform()->GetMatrix());
	movePos = { -333, -212 };
	_slots[12]->GetCollider()->GetTransform()->Move(movePos);
	_instanceDatas[12].matrix = XMMatrixTranspose(_slots[12]->GetCollider()->GetTransform()->GetMatrix());
	movePos.x = -272;
	_slots[13]->GetCollider()->GetTransform()->Move(movePos);
	_instanceDatas[13].matrix = XMMatrixTranspose(_slots[13]->GetCollider()->GetTransform()->GetMatrix());
	movePos.x = -210;
	_slots[14]->GetCollider()->GetTransform()->Move(movePos);
	_instanceDatas[14].matrix = XMMatrixTranspose(_slots[14]->GetCollider()->GetTransform()->GetMatrix());
	movePos.x = -149;
	_slots[15]->GetCollider()->GetTransform()->Move(movePos);
	_instanceDatas[15].matrix = XMMatrixTranspose(_slots[15]->GetCollider()->GetTransform()->GetMatrix());

	movePos = { -326, 278 };
	int index = 16;
	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			Vector2 pos = { movePos.x + (85.5f * x), movePos.y  + (-65.2f * y)};
			_slots[index]->GetCollider()->GetTransform()->Move(pos);
			_instanceDatas[index].matrix = XMMatrixTranspose(_slots[index]->GetCollider()->GetTransform()->GetMatrix());
			index++;
		}
	}

	_instanceBuffer->Update();
}

void Inventory::InstancingIcons()
{
	_itemIcons = make_shared<Quad>(L"Resources/Texture/Item/ItemIcons_10x3.png", _maxFrame);
	_itemIcons->SetVS(ADD_VS(L"Shader/InstancingVertexShader.hlsl"));
	_itemIcons->SetPS(ADD_PS(L"Shader/InstancingPixelShader.hlsl"));

	for (int i = 0; i < _itemIconPoolCount; i++)
	{
		InstanceData instanceData;

		shared_ptr<Transform> transform = make_shared<Transform>();

		instanceData.maxFrame = _maxFrame;
		instanceData.curFrame = {0, 0};
		instanceData.matrix = XMMatrixTranspose(transform->GetMatrix());

		_instanceDatas.emplace_back(instanceData);
	}

	_instanceBuffer = make_shared<VertexBuffer>(_instanceDatas.data(), sizeof(InstanceData), _instanceDatas.size(), 0, true);
}
