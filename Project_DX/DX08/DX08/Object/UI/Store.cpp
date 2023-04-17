#include "framework.h"
#include "Store.h"

Store::Store()
{
	_quad = make_shared<Quad>(L"Resources/Texture/Store/00.png");
	_quad->GetTransform()->Move(Vector2(800, 170));
	_quad->GetTransform()->SetScale(Vector2(2, 2));

	StoreSettings();

	INTERACTOBJ->GetDoor()->SetCallBack(std::bind(&Store::SetRandomItems, this));
}

Store::~Store()
{
}

void Store::Update()
{

	_quad->Update();

	for (auto col : _cols)
	{
		col->Update();
		
		Collision();
	}

	for (auto itemCol : _itemCols)
	{
		itemCol->Update();
	}

	for (auto item : _items)
	{
		item->Update();
	}
}

void Store::Render()
{
	_quad->Render();

	for (auto col : _cols)
		col->Render();

	for (auto itemCol : _itemCols)
		itemCol->Render();

	for (auto item : _items)
	{
		item->Render();
	}
}

void Store::Collision()
{
	if (_player.expired())
		return;

	for (auto col : _cols)
	{
		if (_player.lock()->GetJumpPower() < 0)
		{
			HIT_RESULT result = col->TopBlock(_player.lock()->GetFootCollider());

			if (result.dir == Direction::UP)
				_player.lock()->Ground();
		}
	}
	int index = 0;
	for (auto itemCol : _itemCols)
	{
		HIT_RESULT result = itemCol->IsCollision(_player.lock()->GetFootCollider());

		if (result.isHit)
		{
			if (KEY_DOWN('X'))
			{
				if (INVENTORY->BuyItem(_itemInfos[index].itemCode))
				{
					_itemInfos[index].SetEmpty();
					_items[index]->SetCurFrame(Vector2(0, 0));
				}
			}
		}

		index++;
	}
}

void Store::StoreSettings()
{
	Vector2 tempVec = Vector2(-194, -33);
	for (int i = 0; i < 4; i++)
	{
		shared_ptr<RectCollider> col = make_shared<RectCollider>(Vector2(45, 40));
		col->GetTransform()->SetParent(_quad->GetTransform());
		col->GetTransform()->Move(tempVec);
		_cols.emplace_back(col);

		shared_ptr<CircleCollider> itemCol = make_shared<CircleCollider>(15);
		itemCol->GetTransform()->SetParent(col->GetTransform());
		itemCol->GetTransform()->MoveY(50);
		_itemCols.emplace_back(itemCol);

		shared_ptr<Sprite> sprite = make_shared<Sprite>(L"Resources/Texture/Item/ItemIcons_10x3.png", Vector2(10, 3), Vector2(825, 390));
		sprite->GetTransform()->SetParent(itemCol->GetTransform());
		sprite->SetCurFrame(Vector2(0, 0));
		_items.emplace_back(sprite);

		ItemInfo info = ItemInfo();
		_itemInfos.emplace_back(info);

		tempVec.x += 84;
	}

	tempVec += Vector2(-10, 62);
	shared_ptr<RectCollider> col = make_shared<RectCollider>(Vector2(45, 40));
	col->GetTransform()->SetParent(_quad->GetTransform());
	col->GetTransform()->Move(tempVec);
	_cols.emplace_back(col);
}

void Store::SetRandomItems()
{
	vector<int> indexes;

	for (int i = 10; i < 28; i++)
	{
		if (DATA_M->CheckDuplicate(i) == false)
		{
			indexes.emplace_back(i);
		}
	}
	
	if (indexes.size() < 4)
		return; // TODO : 아이템 총 개수가 4개 보다 작을 시

	std::random_shuffle(indexes.begin(), indexes.end());

	for (int i = 0; i < 4; i++)
	{
		ItemInfo info = DATA_M->GetItemByItemCode(indexes[i]);
		_itemInfos[i] = info;
		_items[i]->SetCurFrame(Vector2(info.frameX, info.frameY));
	}
}