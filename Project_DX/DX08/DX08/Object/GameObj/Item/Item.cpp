#include "framework.h"
#include "Item.h"

Item::Item()
{
	_itemInfo.SetEmpty();

	_item = make_shared<Sprite>(L"Resources/Texture/Item/ItemIcons_10x3.png", Vector2(10, 3), Vector2(825, 390));
	_item->SetCurFrame(Vector2(0, 0));
	_item->GetTransform()->SetScale(Vector2(2, 2));

	_col = make_shared<CircleCollider>(15);
	_col->GetTransform()->SetParent(_item->GetTransform());
}

Item::~Item()
{
}

void Item::Update()
{
	if (_isActive == false)
		return;

	_col->Update();
	_item->Update();
}

void Item::Render()
{
	if (_isActive == false)
		return;

	_item->Render();
	_col->Render();
}

void Item::Activate()
{
	_isActive = true;

	_col->Activate();
}

void Item::DeActivate()
{
	_isActive = false;
	_col->DeActivate();
}

void Item::SetItem(int itemCode)
{
	_itemInfo = DATA_M->GetItemByItemCode(itemCode);
	_item->SetCurFrame(Vector2(_itemInfo.frameX, _itemInfo.frameY));
}
