#include "framework.h"
#include "Door.h"

Door::Door()
{
	CreateAction();
	_sprites[0][0]->GetTransform()->SetPos(CENTER);

	_col = make_shared<RectCollider>(_sprites[0][0]->GetSize());
	_col->GetTransform()->SetParent(_sprites[0][0]->GetTransform());
	_col->GetTransform()->AddScale(Vector2(-0.2f, 0.3f));
	_col->DeActivate();
}

Door::~Door()
{
}

void Door::Update()
{
	if (_isSpawn == false)
		return;

	InteractObj::Update();

	Enter();

	if (_isEntered)
	{
		if (FADEPANEL->GetDelay() < 0.1f)
		{
			_isEntered = false;
			INTERACTOBJ->AddStageLevel();

			switch (_doorType)
			{
			case Door::NORMAL:
				SCENE->SetScene("FieldScene1");
				break;
			case Door::ITEM:
				SCENE->SetScene("FieldScene1");
				break;
			case Door::SKULL:
				SCENE->SetScene("FieldScene1");
				break;
			case Door::ADVANTURER:
				SCENE->SetScene("FieldScene1");
				break;
			case Door::STOREDOOR:
				SCENE->SetScene("StoreScene");
				if (_endEvent != nullptr)
					_endEvent();
				break;
			case Door::BOSS:
				SCENE->SetScene("BossScene");
				break;
			default:
				break;
			}
		}
	}
}

void Door::Render()
{
	if (_isSpawn == false)
		return;

	InteractObj::Render();
}

void Door::Activate()
{
	if (_isActive)
		return;

	_isActive = true;
	_actions[_selected][false]->Reset();
	_sprites[_selected][_isActive]->SetActionClip(_actions[_selected][_isActive]->GetCurClip());
	_actions[_selected][_isActive]->Play();

	_col->Activate();

	SOUND->Play("UI_Open");
}

void Door::SetRandom()
{
	int temp = INTERACTOBJ->GetStageLevel();

	if (temp % 6 == 0)
		_doorType = DoorType::BOSS;
	else if (temp % 3 == 0)
		_doorType = DoorType::STOREDOOR;
	else
		_doorType = static_cast<DoorType>(rand() % 4);

	_actions[_selected][true]->Reset();

	switch (_doorType)
	{
	case Door::NORMAL:
		_selected = 0;
		break;
	case Door::ITEM:
		_selected = 1;
		break;
	case Door::SKULL:
		_selected = 2;
		break;
	case Door::ADVANTURER:
		_selected = 3;
		break;
	case Door::STOREDOOR:
		_selected = 4;
		break;
	case Door::BOSS:
		_selected = 5;
		break;
	case Door::DOORTYPESIZE:
		break;
	default:
		break;
	}
}

void Door::CreateAction()
{
	MyXML::Sort sortX;
	MyXML::Sort sortY;

	string doorType;

	_sprites.resize(6);
	_actions.resize(6);

	for (int i = static_cast<int>(DoorType::NORMAL); i < static_cast<int>(DoorType::DOORTYPESIZE); i++)
	{
		switch (i)
		{
		case DoorType::NORMAL:
			doorType = "Normal";
			break;
		case DoorType::ITEM:
			doorType = "Item";
			break;
		case DoorType::SKULL:
			doorType = "Skull";
			break;
		case DoorType::ADVANTURER:
			doorType = "Advanturer";
			break;
		case DoorType::STOREDOOR:
			doorType = "Store";
			break;
		case DoorType::BOSS:
			doorType = "Boss";
			break;
		default:
			break;
		}

		wstring doorTypeW(doorType.begin(), doorType.end());
		string state;
		string name;
		Action::Type type;
		float speed;

		_sprites[i].resize(2);
		_actions[i].resize(2);
		for (int j = 0; j < 2; j++)
		{
			switch (j)
			{
			case 0:
				state = "Deactivate";
				type = Action::Type::END;
				speed = 0.1f;
				sortX = MyXML::Sort::MIDDLE;
				sortY = MyXML::Sort::BOTTOM;
				break;
			case 1:
				state = "Loop";
				type = Action::Type::LOOP;
				speed = 0.1f;
				sortX = MyXML::Sort::MIDDLE;
				sortY = MyXML::Sort::BOTTOM;
				break;
			default:
				break;
			}

			wstring stateW(state.begin(), state.end());

			wstring srvPath = L"Resources/Texture/InteractObj/Door/" + doorTypeW + stateW + L".png";
			string xmlPath = "Resources/XML/InteractObj/Door/" + doorType + state + ".xml";

			MyXML xml = MyXML(xmlPath, srvPath);

			name = doorType + state;

			_actions[i][j] = make_shared<Action>(xml.GetClips(sortX, sortY), name, type, speed);

			Vector2 maxSize = xml.MaxSize() * 2.0f;
			shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, maxSize);
			_sprites[i][j] = sprite;
		}
	}

	for (auto row : _sprites)
		for (auto sprite : row)
			sprite->GetTransform()->SetParent(_sprites[0][0]->GetTransform());
	_sprites[0][0]->GetTransform()->SetParent(nullptr);
}

void Door::Enter()
{
	if (_isActive == false)
		return;
	
	HIT_RESULT result = _col->IsCollision(PLAYER->GetBodyCollider());
	
	if (result.isHit == false)
		return;
	
	if (KEY_DOWN('X'))
	{
		_isEntered = true;
		FADEPANEL->SetColor({ 0,0,0 });
		FADEPANEL->SetDelay(1.0f);
		FADEPANEL->StartFadeIn();

		SOUND->Play("SkulTeleport");
	}
}