#pragma once
class CupHeadScene : public Scene
{
public:
	CupHeadScene();
	virtual ~CupHeadScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
private:
	shared_ptr<Cup_Advanced_Player> _player;
	shared_ptr<Cup_Monster> _monster;
	shared_ptr<Cup_Bg> _bg;
};

