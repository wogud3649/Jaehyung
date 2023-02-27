#pragma once
class CupHeadScene : public Scene
{
public:
	CupHeadScene();
	virtual ~CupHeadScene();

	virtual void Init() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void Save();
	void Load();
private:
	shared_ptr<Cup_Advanced_Player> _player;
	shared_ptr<Cup_Monster> _monster;
	shared_ptr<Cup_Bg> _bg;

	shared_ptr<Button> _button;
	shared_ptr<Slider> _slider;
};

