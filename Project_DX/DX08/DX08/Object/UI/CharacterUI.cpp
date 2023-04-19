#include "framework.h"
#include "CharacterUI.h"

CharacterUI::CharacterUI()
{
	_characterUI = make_shared<Quad>(L"Resources/Texture/UI/CharacterUI.png");
	_characterUI->GetTransform()->SetPos(Vector2(203.5f, 66.0f));

	_skillIcon = make_shared<Sprite>(L"Resources/Texture/SkillIcon/SkillIcons.png", Vector2(2,3), Vector2(48,72));
	_skillIcon->GetTransform()->SetParent(_characterUI->GetTransform());
	_skillIcon->SetCurFrame(Vector2(0, 0));
	_skillIcon->GetTransform()->SetScale(Vector2(2.0f, 2.0f));
	_skillIcon->GetTransform()->Move(Vector2(-63, 12));

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
	_skillIcon->Update();
	_skullIcon->Update();

	Vector2 curFrame;
	vector<ItemInfo> info = INVENTORY->GetEquipedSkulInfo();
	if (_isFirstSkul)
	{
		curFrame.x = info[0].frameX;
		curFrame.y = info[0].frameY;

		switch (info[0].itemCode)
		{
		case 1:
			_skillIcon->SetCurFrame(Vector2(0, 0));
			break;
		case 2:
			_skillIcon->SetCurFrame(Vector2(0, 1));
			break;
		default:
			break;
		}
	}
	else
	{
		curFrame.x = info[1].frameX;
		curFrame.y = info[1].frameY;

		switch (info[1].itemCode)
		{
		case 1:
			_skillIcon->SetCurFrame(Vector2(0, 0));
			break;
		case 2:
			_skillIcon->SetCurFrame(Vector2(0, 1));
			break;
		default:
			break;
		}
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
	_skillIcon->Render();

	if (_activeExtraSkillSlot)
		_extraSkillSlot->Render();
	if (_activeOrbSlot)
		_orbSlot->Render();
	
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

	_sliderHp->PostRender();
}

void CharacterUI::SetHpRatio(float ratio)
{
	_sliderHp->SetRatio(ratio);
}