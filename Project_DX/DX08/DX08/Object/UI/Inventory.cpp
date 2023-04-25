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

	_selectedFrame = make_shared<Slider>(L"Resources/Texture/UI/SelectedFrame.png");

	CreateSlots();
	RootItem(1);
	DATA_M->SetDuplicate(1);

	shared_ptr<Sprite> skillIcon1= make_shared<Sprite>(L"Resources/Texture/SkillIcon/SkillIcons.png",Vector2(2,3), Vector2(48,72));
	shared_ptr<Sprite> skillIcon2 = make_shared<Sprite>(L"Resources/Texture/SkillIcon/SkillIcons.png",Vector2(2,3), Vector2(48,72));

	_skillIcons.emplace_back(skillIcon1);
	_skillIcons.emplace_back(skillIcon2);

	for (auto skillIcon : _skillIcons)
	{
		skillIcon->GetTransform()->SetScale(Vector2(2, 2));
		skillIcon->GetTransform()->SetPos(Vector2(-50, -50));
	}
}

Inventory::~Inventory()
{
}

void Inventory::Update()
{
	if (KEY_DOWN('I'))
		_inventoryOpen = !_inventoryOpen;

	if (_curMoney < _goalMoney)
	{
		if (_curMoney > _goalMoney - 100)
			_curMoney++;
		else
			_curMoney = LERP(_curMoney, _goalMoney, 0.02f);
	}
	if (_curMoney > _goalMoney)
	{
		if (_curMoney < _goalMoney + 100)
			_curMoney--;
		else
			_curMoney = LERP(_curMoney, _goalMoney, 0.02f);
	}

	if (_inventoryOpen == false)
		return;

	_inventory->Update();
	_inventoryPannels->Update();
	_itemInfoIcons->Update();

	for (auto skillIcon : _skillIcons)
		skillIcon->Update();

	if (KEY_DOWN('A'))
	{
		_activeExtraInventory = !_activeExtraInventory;
		if (_activeExtraInventory)
			_curSelected = 16;
		else
			_curSelected = 0;
	}

	if (KEY_DOWN(VK_RBUTTON))
	{
		_detailedInfo = !_detailedInfo;
		SetInfoPannels();
	}

	if (KEY_DOWN(VK_UP))
		_curSelected -= 3;
	if (KEY_DOWN(VK_DOWN))
		_curSelected += 3;
	if (KEY_DOWN(VK_LEFT))
		_curSelected -= 1;
	if (KEY_DOWN(VK_RIGHT))
		_curSelected += 1;

	if (_activeExtraInventory)
	{
		if (_curSelected < 16)
			_curSelected = _maxSlot - 1;
		else if (_curSelected > _maxSlot - 1)
			_curSelected = 16;
		_extraInventory->Update();

		for (int i = 16; i < _maxSlot; i++)
		{
			_slots[i]->Update();
			if (_slots[i]->IsCollision(MOUSE_POS))
			{
				_curSelected = i;
				if (KEY_DOWN(VK_LBUTTON))
					EquipItem(i);
			}
		}
	}
	else
	{
		if (_curSelected > 15)
			_curSelected = 0;
		else if (_curSelected < 0)
			_curSelected = 15;
		for (int i = 0; i < 16; i++)
		{
			_slots[i]->Update();
			if (_slots[i]->IsCollision(MOUSE_POS))
			{
				_curSelected = i;
				if (KEY_DOWN(VK_LBUTTON))
					TakeOffItem(i);
			}
		}
	}

	if (_curSelected != _oldSelected)
		SetInfoPannels();

	if (_itemChanged)
		SetPlayerStats();

	if (_curSelected != -1)
	{
		_selectedFrame->Update();
		if (_itemDatas[_curSelected].itemCode != 0)
		{
			if (KEY_PRESS('X'))
			{
				_curItemSellDelay -= DELTA_TIME;

				if (_curItemSellDelay < 0)
				{
					_curItemSellDelay = _maxItemSellDelay;

					SellItem(_curSelected);
				}
			}
			else
			{
				_curItemSellDelay = _maxItemSellDelay;
			}
		}
		else
		{
			_curItemSellDelay = _maxItemSellDelay;
		}

		_selectedFrame->SetRatio(_curItemSellDelay / _maxItemSellDelay);
	}
}

void Inventory::PostRender()
{
	if (_inventoryOpen == false)
		return;

	_inventory->Render();
	_inventoryPannels->Render();
	_itemInfoIcons->Render();

	for (auto skillIcon : _skillIcons)
		skillIcon->Render();
	
	if (_activeExtraInventory)
	{
		_extraInventory->Render();
		_instanceBuffer->IASet(1);
		_itemIcons->SetRender();
		DC->DrawIndexedInstanced(6, 27, 0, 0, 16);

		for (int i = 16; i < _maxSlot; i++)
			_slots[i]->Render();

		if (_curSelected != -1 && _curSelected > 15)
			_selectedFrame->PostRender();
	}
	else
	{
		_instanceBuffer->IASet(1);
		_itemIcons->SetRender();
		DC->DrawIndexedInstanced(6, 16, 0, 0, 0);
		for (int i = 0; i < 16; i++)
			_slots[i]->Render();

		if (_curSelected != -1 && _curSelected < 16)
			_selectedFrame->PostRender();
	}

}

void Inventory::SetInfoPannels()
{
	if (_curSelected > 42)
		_curSelected = 0;
	else if (_curSelected < 0)
		_curSelected = 42;

	ItemInfo info = _itemDatas[_curSelected];
	_itemInfoIcons->SetCurFrame(Vector2(info.frameX, info.frameY));
	_selectedFrame->SetPos(_slots[_curSelected]->GetCollider()->GetTransform()->GetWorldPos());
	_oldSelected = _curSelected;
	
	if (_statusOpen)
		_curPannel = Inventory::STATUS;
	else if (info.itemType == ItemType::HEAD)
	{
		if (_itemDatas[_curSelected].itemCode == 1)
			_skillIcons[0]->SetCurFrame(Vector2(0, 0));
		else if (_itemDatas[_curSelected].itemCode == 2 || _itemDatas[_curSelected].itemCode == 4 || _itemDatas[_curSelected].itemCode == 6 || _itemDatas[_curSelected].itemCode == 8)
		{
			_skillIcons[0]->SetCurFrame(Vector2(0, 1));
			_skillIcons[1]->SetCurFrame(Vector2(1, 1));
		}
		else if (_itemDatas[_curSelected].itemCode == 3 || _itemDatas[_curSelected].itemCode == 5 || _itemDatas[_curSelected].itemCode == 7 || _itemDatas[_curSelected].itemCode == 9)
		{
			_skillIcons[0]->SetCurFrame(Vector2(0, 2));
			_skillIcons[1]->SetCurFrame(Vector2(1, 2));
		}

		if (info.rarity < Rarity::RARE)
		{
			if (_detailedInfo)
			{
				_curPannel = Inventory::SINGLE_SKUL_SLOT_LONG;
				_skillIcons[0]->GetTransform()->SetPos(Vector2(866, 350));
				_skillIcons[1]->GetTransform()->SetPos(Vector2(-50, -50));
			}
			else
			{
				_curPannel = Inventory::SINGLE_SKUL_SLOT_SHORT;
				_skillIcons[0]->GetTransform()->SetPos(Vector2(866, 150));
				_skillIcons[1]->GetTransform()->SetPos(Vector2(-50, -50));
			}
		}
		else
		{
			if (_detailedInfo)
			{
				_curPannel = Inventory::DOUBLE_SKUL_SLOT_LONG;
				_skillIcons[0]->GetTransform()->SetPos(Vector2(705, 350));
				_skillIcons[1]->GetTransform()->SetPos(Vector2(1027, 350));
			}
			else
			{
				_curPannel = Inventory::DOUBLE_SKUL_SLOT_SHORT;
				_skillIcons[0]->GetTransform()->SetPos(Vector2(705, 150));
				_skillIcons[1]->GetTransform()->SetPos(Vector2(1027, 150));
			}
		}
	}
	else if (info.itemType == ItemType::EQUIPMENT)
	{
		if (_detailedInfo)
			_curPannel = Inventory::DOUBLE_ITEM_SLOT_LONG;
		else
			_curPannel = Inventory::DOUBLE_ITEM_SLOT_SHORT;
	}
	else if (info.itemType == ItemType::ORB)
		_curPannel = Inventory::ORB_SLOT;
	else
	{
		_curPannel = Inventory::EMPTY;
		_skillIcons[0]->GetTransform()->SetPos(Vector2(-50, -50));
		_skillIcons[1]->GetTransform()->SetPos(Vector2(-50, -50));
	}

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
		_itemChanged = true;

		_itemDatas[index].SetEmpty();
		_instanceDatas[index].curFrame = Vector2(0, 0);
		_instanceBuffer->Update();
	}
}

void Inventory::TakeOffItem(int index)
{
	if (index == -1)
		return;

	if (index == 0)
	{
		if (_itemDatas[1].itemCode == 0)
			return;

		if (PLAYER->GetIsFirstSkul())
			PLAYER->SwapSkul();
	}
	else if (index == 1)
	{
		if (_itemDatas[0].itemCode == 0)
			return;

		if (!PLAYER->GetIsFirstSkul())
			PLAYER->SwapSkul();
	}

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
	if (index == 0)
	{
		if (_itemDatas[1].itemCode == 0)
			return;
	}
	else if (index == 1)
	{
		if (_itemDatas[0].itemCode == 0)
			return;
	}

	_itemDatas[index].SetEmpty();
	_instanceDatas[index].curFrame = Vector2(0, 0);
	_instanceBuffer->Update();

	_itemChanged = true;
}

bool Inventory::SellItem(int index)
{
	if (index == -1)
		return false;

	if (index == 0)
		if (_itemDatas[1].itemCode == 0)
			return false;

	else if (index == 1)
		if (_itemDatas[0].itemCode == 0)
			return false;

	ItemInfo info = _itemDatas[index];
	if (info.itemCode == 0)
		return false;

	if (info.itemType == ItemType::HEAD)
		_boneFrag += info.price;
	else
		AddMoney(info.price);

	RemoveItem(index);

	return true;
}

bool Inventory::BuyItem(int itemCode)
{
	if (itemCode == 0)
		return false;

	int price = DATA_M->GetItemByItemCode(itemCode).price;

	if (_goalMoney < price)
		return false;

	bool success = RootItem(itemCode);
	if (success)
		ReduceMoney(price);

	return true;
}

bool Inventory::RootItem(int itemCode)
{
	ItemInfo info = DATA_M->GetItemByItemCode(itemCode);
	if (info.itemCode == 0)
		return false;

	DATA_M->SetDuplicate(itemCode);
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

	_itemChanged = true;
	
	_instanceBuffer->Update();
	return true;
}

void Inventory::SetPlayerStats()
{
	PLAYER->SetEquipStats(this->GetEquipStats());
}

void Inventory::AddMoney(int money)
{
	if (money < 0)
		return;

	_goalMoney += money;
}

void Inventory::ReduceMoney(int money)
{
	if (money < 0)
		return;
	
	_goalMoney -= money;
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
