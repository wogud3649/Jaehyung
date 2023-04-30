#include "framework.h"
#include "Chest.h"

Chest::Chest()
{
	CreateAction();
	_sprites[0][0]->GetTransform()->SetPos(CENTER);

	_col = make_shared<RectCollider>(_sprites[0][0]->GetSize());
	_col->GetTransform()->SetParent(_sprites[0][0]->GetTransform());
	_col->DeActivate();

	_actions[_selected][_isActive]->Play();
	
	_item = make_shared<Item>();
	_item->DeActivate();

	_potion = make_shared<Potion>();
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
		_potion->Update();
		ItemPop();

		_itemActivateDelay -= DELTA_TIME;
		if (_itemActivateDelay <= 0.0f)
			TakeItem();
	}
}

void Chest::Render()
{
	if (_isSpawn == false)
		return;

	InteractObj::Render();

	if (_isOpen)
	{
		_item->Render();
		_potion->Render();
	}
}

void Chest::Spawn()
{
	if (_isSpawn)
		return;

	_isSpawn = true;
	_popSpeed = 700.0f;
	_itemActivateDelay = 1.2f;
	_col->Activate();
}

void Chest::Extinct()
{
	InteractObj::Extinct();
	_isOpen = false;
}

void Chest::SetRandom()
{
	int temp = rand() % 18 + 10;
	bool check = false;
	
	for (int i = 10; i < 28; i++)
	{
		if (true/*DATA_M->CheckDuplicate(i) == false*/)
		{
			check = true;
			break;
		}
	}

	if (check == false)
		return;

	while (false/*DATA_M->CheckDuplicate(temp)*/)
		int temp = rand() % 18 + 10;
	
	if (temp < 17)
	{
		_rarity = Rarity::NORMAL;
		_selected = 0;
	}
	else if (temp < 21)
	{
		_rarity = Rarity::RARE;
		_selected = 1;
	}
	else if (temp < 25)
	{
		_rarity = Rarity::UNIQUE;
		_selected = 2;
	}
	else if (temp < 28)
	{
		_rarity = Rarity::LEGENDARY;
		_selected = 3;
	}

	_item->SetItem(temp);
	_item->SetPos(_sprites[0][0]->GetTransform()->GetWorldPos());
}

void Chest::CreateAction()
{
	MyXML::Sort sortX;
	MyXML::Sort sortY;

	string rarity;

	_sprites.resize(4);
	_actions.resize(4);

	for (int i = static_cast<int>(Rarity::NORMAL); i < static_cast<int>(Rarity::RARITYSIZE); i++)
	{
		switch (i)
		{
		case static_cast<int>(Rarity::NORMAL):
			rarity = "N";
			break;
		case static_cast<int>(Rarity::RARE):
			rarity = "R";
			break;
		case static_cast<int>(Rarity::UNIQUE):
			rarity = "U";
			break;
		case static_cast<int>(Rarity::LEGENDARY):
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

		_sprites[i-1].resize(2);
		_actions[i-1].resize(2);
		for (int j = 0; j < 2; j++)
		{
			switch (j)
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

			_actions[i-1][j] = make_shared<Action>(xml.GetClips(sortX, sortY), name, type, speed);

			Vector2 maxSize = xml.MaxSize() * 2.0f;
			shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, maxSize);
			_sprites[i-1][j] = sprite;
		}
	}

	for (auto row : _sprites)
		for (auto sprite : row)
			sprite->GetTransform()->SetParent(_sprites[0][0]->GetTransform());
	_sprites[0][0]->GetTransform()->SetParent(nullptr);
	_sprites[0][1]->GetTransform()->MoveY(5);
	_sprites[1][1]->GetTransform()->MoveY(5);
	_sprites[2][1]->GetTransform()->MoveY(5);
	_sprites[3][1]->GetTransform()->MoveY(5);
}

void Chest::OpenChest()
{
	if (_isOpen)
		return;

	HIT_RESULT result = _col->IsCollision(PLAYER->GetBodyCollider());
	if (result.isHit)
	{
		if (KEY_DOWN('X'))
		{
			INTERACTOBJ->GetDoor()->Activate();
			Activate();
			_col->DeActivate();
			_isOpen = true;
			_potion->SetPos(_col->GetTransform()->GetWorldPos());
			_potion->Activate();

			SOUND->Play("Object_OpenBox");
		}
	}
}

void Chest::ItemPop()
{
	if (_item->GetPos().y < _sprites[_selected][0]->GetTransform()->GetWorldPos().y)
		return;

	if (_item->GetActive() == false)
		_item->Activate();

	_item->MoveY(_popSpeed * DELTA_TIME);
	_popSpeed -= (GRAVITY * GRAVITY * DELTA_TIME);
}

void Chest::TakeItem()
{
	if (_item->GetActive() == false)
		return;

	HIT_RESULT result = _item->GetCollider()->IsCollision(PLAYER->GetBodyCollider());
	if (result.isHit == false)
		return;

	if (KEY_DOWN('X'))
	{
		INVENTORY->RootItem(_item->GetItem());
		_item->DeActivate();

		SOUND->Play("GetItem");
	}
}