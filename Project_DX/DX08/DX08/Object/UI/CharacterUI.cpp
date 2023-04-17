#include "framework.h"
#include "CharacterUI.h"

CharacterUI::CharacterUI()
{
	_characterUI = make_shared<Quad>(L"Resources/Texture/UI/CharacterUI.png");
	_characterUI->GetTransform()->SetPos(Vector2(203.5f, 66.0f));

	_extraSkillSlot = make_shared<Quad>(L"Resources/Texture/UI/ExtraSkillSlot.png");
	_extraSkillSlot->GetTransform()->SetParent(_characterUI->GetTransform());

	_orbSlot = make_shared<Quad>(L"Resources/Texture/UI/OrbSlot.png");
	_orbSlot->GetTransform()->SetParent(_characterUI->GetTransform());

	_skullIcon = make_shared<Sprite>(L"Resources/Texture/Item/SkullIcons_10x1.png", Vector2(10, 1), Vector2(3300, 520));
	_skullIcon->GetTransform()->SetParent(_characterUI->GetTransform());
	_skullIcon->GetTransform()->Move(Vector2(-145, 19));
	_skullIcon->GetTransform()->SetScale(Vector2(0.7f, 0.7f));
}

CharacterUI::~CharacterUI()
{
}

void CharacterUI::Init()
{
}

void CharacterUI::Update()
{
	_characterUI->Update();
	_skullIcon->Update();

	Vector2 curFrame;
	if (_isFirstSkul)
	{
		curFrame.x = INVENTORY->GetEquipedSkulInfo()[0].frameX;
		curFrame.y = INVENTORY->GetEquipedSkulInfo()[0].frameY;
	}
	else
	{
		curFrame.x = INVENTORY->GetEquipedSkulInfo()[1].frameX;
		curFrame.y = INVENTORY->GetEquipedSkulInfo()[1].frameY;
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
}

void CharacterUI::SwapSkul()
{
	if (_isFirstSkul)
	{
		if (INVENTORY->GetEquipedSkulInfo()[1].itemCode == 0)
			return;
		_isFirstSkul = false;
	}
	else
	{
		if (INVENTORY->GetEquipedSkulInfo()[0].itemCode == 0)
			return;
		_isFirstSkul = true;
	}
}