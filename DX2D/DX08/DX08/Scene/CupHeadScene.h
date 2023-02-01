#pragma once
class CupHeadScene : public Scene
{
public:
	CupHeadScene();
	~CupHeadScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Cup_Player> _player;
};

