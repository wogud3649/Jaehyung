#pragma once
class BossScene : public Scene
{
public:
	BossScene();
	~BossScene();

	virtual void Init() override;
	virtual void Fin() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void PostRender() override;

private:
	void SceneClear();
	void CreateInteractObj();

	shared_ptr<Brick> _brick;
	shared_ptr<Slider> _healthBar;
};

