#include "framework.h"
#include "ItemIcon.h"

ItemIcon::ItemIcon()
{
	_sprite = make_shared<Sprite>(L"Resource/Texture/Item_11x5.png", Vector2(11, 5), Vector2(55, 55));

	_button = make_shared<Button>(Vector2(55, 55));
	_button->SetParent(_sprite->GetTransform());
	// TODO : callBack;
}

ItemIcon::~ItemIcon()
{
}

void ItemIcon::Update()
{
	_sprite->Update();
	_button->Update();
}

void ItemIcon::Render()
{
	_sprite->Render();
	_button->PostRender();
}
