#include "framework.h"
#include "Chest.h"

Chest::Chest()
{
	_rarity = static_cast<Rarity>((rand() % 4) + 1);

	CreateAction();
	_sprites[0]->GetTransform()->SetPos(CENTER);
	_sprites[1]->GetTransform()->SetParent(_sprites[0]->GetTransform());
	_sprites[1]->GetTransform()->MoveY(5);

	_actions[_isActive]->Play();
}

Chest::~Chest()
{
}

void Chest::Update()
{
	InteractObj::Update();

	if (KEY_DOWN(VK_RBUTTON))
		SetActive();
}

void Chest::Render()
{
	InteractObj::Render();
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

void Chest::SetActive()
{
	InteractObj::SetActive();
}