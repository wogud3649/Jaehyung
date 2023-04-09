#include "framework.h"
#include "Chest.h"

Chest::Chest()
{
	_rarity = static_cast<Rarity>((rand() % 4) + 1);

	CreateAction();
	_sprites[0]->GetTransform()->SetPos(CENTER);
	_sprites[1]->GetTransform()->SetParent(_sprites[0]->GetTransform());
	_sprites[1]->GetTransform()->MoveY(5);

	_col = make_shared<RectCollider>(_sprites[0]->GetSize());
	_col->GetTransform()->SetParent(_sprites[0]->GetTransform());

	_actions[_isActive]->Play();

	_item = make_shared<Sprite>(L"Resources/Texture/Item/ItemIcons_10x3.png", Vector2(10, 3), Vector2(825, 390));
	_item->SetCurFrame(Vector2(0, 0));
	_item->GetTransform()->SetParent(_sprites[0]->GetTransform());
	_item->GetTransform()->SetScale(Vector2(2, 2));
}

Chest::~Chest()
{
}

void Chest::Update()
{
	if (_isSpawn == false)
		return;
	
	InteractObj::Update();

	OpenChest();

	if (_isOpen)
	{
		_item->Update();
		ItemPop();
	}
}

void Chest::Render()
{
	if (_isSpawn == false)
		return;
	
	InteractObj::Render();

	if (_isOpen)
		_item->Render();
}

void Chest::CreateAction()
{
	MyXML::Sort sortX;
	MyXML::Sort sortY;

	string rarity;
	switch (_rarity)
	{
	case Rarity::NORMAL:
		rarity = "N";
		break;
	case Rarity::RARE:
		rarity = "R";
		break;
	case Rarity::UNIQUE:
		rarity = "U";
		break;
	case Rarity::LEGENDARY:
		rarity = "L";
		break;
	default:
		break;
	}

	wstring rarityW(rarity.begin(), rarity.end());
	string state;
	string name;
	Action::Type type;
	float speed;

	for (int i = 0; i < 2; i++)
	{
		switch (i)
		{
		case 0:
			state = "Idle";
			type = Action::Type::END;
			speed = 0.1f;
			sortX = MyXML::Sort::MIDDLE;
			sortY = MyXML::Sort::BOTTOM;
			break;
		case 1:
			state = "Open";
			type = Action::Type::END;
			speed = 0.1f;
			sortX = MyXML::Sort::MIDDLE;
			sortY = MyXML::Sort::BOTTOM;
			break;
		default:
			break;
		}
		
		wstring stateW(state.begin(), state.end());

		wstring srvPath = L"Resources/Texture/InteractObj/Chest/" + rarityW + stateW + L".png";
		string xmlPath = "Resources/XML/InteractObj/Chest/" + rarity + state + ".xml";

		MyXML xml = MyXML(xmlPath, srvPath);

		name = rarity + state;

		_actions.emplace_back(make_shared<Action>(xml.GetClips(sortX, sortY), name, type, speed));

		Vector2 maxSize = xml.MaxSize() * 2.0f;
		shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, maxSize);
		_sprites.emplace_back(sprite);
	}
}

void Chest::OpenChest()
{
	if (_isOpen)
		return;
	if (_player.expired())
		return;

	HIT_RESULT result = _col->IsCollision(_player.lock()->GetBodyCollider());
	if (result.isHit)
	{
		if (KEY_DOWN('X'))
		{
			Activate();
			_isOpen = true;

			switch (_rarity)
			{
			case Rarity::NORMAL:
				RandomNormal();
				break;
			case Rarity::RARE:
				RandomRare();
				break;
			case Rarity::UNIQUE:
				RandomUnique();
				break;
			case Rarity::LEGENDARY:
				RandomLegendary();
				break;
			default:
				break;
			}
		}
	}
}

void Chest::ItemPop()
{
	if (_item->GetTransform()->GetWorldPos().y < _sprites[0]->GetTransform()->GetWorldPos().y)
		return;

	_item->GetTransform()->MoveY(_popSpeed * DELTA_TIME);
	_popSpeed -= (GRAVITY * GRAVITY * DELTA_TIME);
}

void Chest::RandomNormal()
{
	int temp = rand() % 7 + 10;
	ItemInfo itemInfo = DATA_M->GetItemByItemCode(temp);

	_item->SetCurFrame(Vector2(itemInfo.frameX, itemInfo.frameY));
}

void Chest::RandomRare()
{
	int temp = rand() % 4 + 18;
	ItemInfo itemInfo = DATA_M->GetItemByItemCode(temp);

	_item->SetCurFrame(Vector2(itemInfo.frameX, itemInfo.frameY));
}

void Chest::RandomUnique()
{
	int temp = rand() % 4 + 22;
	ItemInfo itemInfo = DATA_M->GetItemByItemCode(temp);

	_item->SetCurFrame(Vector2(itemInfo.frameX, itemInfo.frameY));
}

void Chest::RandomLegendary()
{
	int temp = rand() % 3 + 26;
	ItemInfo itemInfo = DATA_M->GetItemByItemCode(temp);

	_item->SetCurFrame(Vector2(itemInfo.frameX, itemInfo.frameY));
}

void Chest::Activate()
{
	InteractObj::Activate();
}