#include "framework.h"
#include "Door.h"

Door::Door()
{
	_doorType = static_cast<DoorType>(rand() % 6);

	CreateAction();
	_sprites[0]->GetTransform()->SetPos(CENTER);
	_sprites[1]->GetTransform()->SetParent(_sprites[0]->GetTransform());

	_col = make_shared<RectCollider>(_sprites[0]->GetSize());
	_col->GetTransform()->SetParent(_sprites[0]->GetTransform());
	_col->GetTransform()->AddScale(Vector2(-0.2f, 0.3f));

	_actions[_isActive]->Play();
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
}

void Door::Render()
{
	if (_isSpawn == false)
		return;

	InteractObj::Render();
}

void Door::CreateAction()
{
	MyXML::Sort sortX;
	MyXML::Sort sortY;

	string doorType;
	switch (_doorType)
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
	case DoorType::STORE:
		doorType = "Store";
		break;
	case DoorType::ADVANTURER:
		doorType = "Advanturer";
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

	for (int i = 0; i < 2; i++)
	{
		switch (i)
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

		_actions.emplace_back(make_shared<Action>(xml.GetClips(sortX, sortY), name, type, speed));

		Vector2 maxSize = xml.MaxSize() * 2.0f;
		shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, maxSize);
		_sprites.emplace_back(sprite);
	}
}

void Door::Enter()
{
	if (_player.expired())
		return;
	if (_isActive == false)
		return;
	
	HIT_RESULT result = _col->IsCollision(_player.lock()->GetBodyCollider());
	
	if (result.isHit == false)
		return;
	
	if (KEY_DOWN('X'))
	{
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
		case Door::STORE:
			break;
		case Door::ADVANTURER:
			SCENE->SetScene("FieldScene1");
			break;
		case Door::BOSS:
			SCENE->SetScene("BossScene");
			break;
		default:
			break;
		}
	}
}

void Door::Activate()
{
	InteractObj::Activate();
}