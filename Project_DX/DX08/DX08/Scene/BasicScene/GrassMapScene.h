#pragma once
class GrassMapScene : public Scene
{
public:
	GrassMapScene();
	~GrassMapScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Brick> _brick;

	shared_ptr<Advanced_Player> _player;
};

