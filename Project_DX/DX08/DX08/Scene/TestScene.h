#pragma once
class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	virtual void Update() override;
	virtual void Render() override;
private:
	shared_ptr<Player> _player;
};

