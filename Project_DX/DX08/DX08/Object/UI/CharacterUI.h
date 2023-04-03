#pragma once
class CharacterUI
{
public:
	CharacterUI();
	~CharacterUI();

	void Update();
	void PostRender();

private:
	shared_ptr<Quad> _characterUI;

	shared_ptr<Quad> _extraSkillSlot;
	bool _activeExtraSkillSlot = false;
	
	shared_ptr<Quad> _orbSlot;
	bool _activeOrbSlot = false;

	shared_ptr<Sprite> _skullIcon;
};