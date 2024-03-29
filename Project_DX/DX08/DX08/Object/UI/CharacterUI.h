#pragma once
class CharacterUI
{
public:
	CharacterUI();
	~CharacterUI();

	void Init();
	void Update();
	void PostRender();

	void SetHpRatio(float ratio);
	void SetSkillRatio(int index, float ratio);
	void SwapSkul(bool isFirstSkul) { _isFirstSkul = isFirstSkul; }

private:
	shared_ptr<Quad> _characterUI;

	vector<shared_ptr<SpriteSlider>> _skillIcons;

	shared_ptr<Quad> _extraSkillSlot;
	bool _activeExtraSkillSlot = false;
	
	shared_ptr<Quad> _orbSlot;
	bool _activeOrbSlot = false;

	shared_ptr<Sprite> _skullIcon;

	shared_ptr<Slider> _sliderHp;

	bool _isFirstSkul = true;
};