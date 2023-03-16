#pragma once
class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	virtual void Init() override;
	virtual void Fin() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void PostRender() override;

private:
	shared_ptr<Advanced_Player> _player;
	shared_ptr<Brick> _brick;
};

