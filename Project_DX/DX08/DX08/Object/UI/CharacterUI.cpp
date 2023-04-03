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
	_skullIcon->SetCurFrame(Vector2(9, 0));
}

CharacterUI::~CharacterUI()
{
}

void CharacterUI::Update()
{
	_characterUI->Update();
	_skullIcon->Update();

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
}
