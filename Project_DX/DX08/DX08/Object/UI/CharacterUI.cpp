#include "framework.h"
#include "CharacterUI.h"

CharacterUI::CharacterUI()
{
	_characterUI = make_shared<Quad>(L"Resources/Texture/UI/CharacterUI.png");
	_characterUI->GetTransform()->SetPos(Vector2(203.5f, 66.0f));

	shared_ptr<SpriteSlider> skillIcon = make_shared<SpriteSlider>(L"Resources/Texture/SkillIcon/SkillIcons.png", Vector2(2,3));
	skillIcon->GetTransform()->SetParent(_characterUI->GetTransform());
	skillIcon->SetCurFrame(Vector2(0, 0));
	skillIcon->GetTransform()->SetScale(Vector2(2.0f, 2.0f));
	skillIcon->GetTransform()->Move(Vector2(-63, 12));
	_skillIcons.emplace_back(skillIcon);

	skillIcon = make_shared<SpriteSlider>(L"Resources/Texture/SkillIcon/SkillIcons.png", Vector2(2, 3));
	skillIcon->GetTransform()->SetParent(_characterUI->GetTransform());
	skillIcon->SetCurFrame(Vector2(0, 0));
	skillIcon->GetTransform()->SetScale(Vector2(2.0f, 2.0f));
	skillIcon->GetTransform()->Move(Vector2(0, 12));
	_skillIcons.emplace_back(skillIcon);

	_extraSkillSlot = make_shared<Quad>(L"Resources/Texture/UI/ExtraSkillSlot.png");
	_extraSkillSlot->GetTransform()->SetParent(_characterUI->GetTransform());

	_orbSlot = make_shared<Quad>(L"Resources/Texture/UI/OrbSlot.png");
	_orbSlot->GetTransform()->SetParent(_characterUI->GetTransform());

	_skullIcon = make_shared<Sprite>(L"Resources/Texture/Item/SkullIcons_10x1.png", Vector2(10, 1), Vector2(3300, 520));
	_skullIcon->GetTransform()->SetParent(_characterUI->GetTransform());
	_skullIcon->GetTransform()->Move(Vector2(-145, 19));
	_skullIcon->GetTransform()->SetScale(Vector2(0.7f, 0.7f));

	_sliderHp = make_shared<Slider>();
	Vector2 tempPos = _characterUI->GetTransform()->GetPos();
	tempPos.y -= 32;
	_sliderHp->SetPos(tempPos);
}

CharacterUI::~CharacterUI()
{
}

void CharacterUI::Init()
{
}

void CharacterUI::Update()
{
	_sliderHp->Update();
	_characterUI->Update();
	for (auto skillIcon : _skillIcons)
		skillIcon->Update();
	_skullIcon->Update();

	Vector2 curFrame;
	vector<ItemInfo> info = INVENTORY->GetEquipedSkulInfo();

	if (info[!_isFirstSkul].rarity == Rarity::NONE || info[!_isFirstSkul].rarity == Rarity::NORMAL)
		_activeExtraSkillSlot = false;
	else
		_activeExtraSkillSlot = true;

	curFrame.x = info[!_isFirstSkul].frameX;
	curFrame.y = info[!_isFirstSkul].frameY;

	switch (info[!_isFirstSkul].itemCode)
	{
	case 1:
		_skillIcons[0]->SetCurFrame(Vector2(0, 0));
		_skillIcons[1]->SetCurFrame(Vector2(1, 0));
		break;
	case 2:
		_skillIcons[0]->SetCurFrame(Vector2(0, 1));
		_skillIcons[1]->SetCurFrame(Vector2(1, 1));
		break;
	case 3:
		_skillIcons[0]->SetCurFrame(Vector2(0, 2));
		_skillIcons[1]->SetCurFrame(Vector2(1, 2));
		break;
	case 4:
		_skillIcons[0]->SetCurFrame(Vector2(0, 1));
		_skillIcons[1]->SetCurFrame(Vector2(1, 1));
		break;
	case 5:
		_skillIcons[0]->SetCurFrame(Vector2(0, 2));
		_skillIcons[1]->SetCurFrame(Vector2(1, 2));
		break;
	case 6:
		_skillIcons[0]->SetCurFrame(Vector2(0, 1));
		_skillIcons[1]->SetCurFrame(Vector2(1, 1));
		break;
	case 7:
		_skillIcons[0]->SetCurFrame(Vector2(0, 2));
		_skillIcons[1]->SetCurFrame(Vector2(1, 2));
		break;
	case 8:
		_skillIcons[0]->SetCurFrame(Vector2(0, 1));
		_skillIcons[1]->SetCurFrame(Vector2(1, 1));
		break;
	case 9:
		_skillIcons[0]->SetCurFrame(Vector2(0, 2));
		_skillIcons[1]->SetCurFrame(Vector2(1, 2));
		break;
	default:
		break;
	}

	_skullIcon->SetCurFrame(curFrame);

	if (_activeExtraSkillSlot)
		_extraSkillSlot->Update();
	if (_activeOrbSlot)
		_orbSlot->Update();
}

void CharacterUI::PostRender()
{
	_characterUI->Render();
	_skullIcon->Render();

	if (_activeExtraSkillSlot)
		_extraSkillSlot->Render();
	if (_activeOrbSlot)
		_orbSlot->Render();

	for (auto skillIcon : _skillIcons)
		skillIcon->PostRender();
	
	wstring money = L"Money : " + to_wstring(INVENTORY->GetMoney());
	RECT rect;
	rect.left = WIN_WIDTH - 200;
	rect.right = WIN_WIDTH;
	rect.top = WIN_HEIGHT - 60;
	rect.bottom = WIN_HEIGHT;
	DirectWrite::GetInstance()->RenderText(money, rect);
	wstring boneFrag = L"BoneFrag : " + to_wstring(INVENTORY->GetBoneFrag());
	rect.top = WIN_HEIGHT - 30;
	DirectWrite::GetInstance()->RenderText(boneFrag, rect);

	wstring maxHp = to_wstring(static_cast<int>(PLAYER->GetMaxHp()));
	wstring curHp = to_wstring(static_cast<int>(PLAYER->GetCurHp()));
	wstring hpBar = curHp + L" / " + maxHp;
	rect.left = 165;
	rect.right = 265;
	rect.top = WIN_HEIGHT - 50;
	rect.bottom = WIN_HEIGHT;
	DirectWrite::GetInstance()->RenderText(hpBar, rect);

	_sliderHp->PostRender();
}

void CharacterUI::SetHpRatio(float ratio)
{
	_sliderHp->SetRatio(ratio);
}

void CharacterUI::SetSkillRatio(int index, float ratio)
{
	_skillIcons[index]->SetRatio(ratio);
}
