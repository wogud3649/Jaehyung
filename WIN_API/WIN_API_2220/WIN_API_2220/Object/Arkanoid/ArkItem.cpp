#include "framework.h"
#include "ArkItem.h"

ArkItem::ArkItem(Vector2 pos)
{
	_item = make_shared<CircleCollider>(pos, _radius);
}

ArkItem::~ArkItem()
{
}

void ArkItem::Update()
{
	_item->Update();
}

void ArkItem::Render(HDC hdc)
{
	_item->Render(hdc);
}