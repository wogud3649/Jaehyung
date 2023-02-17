#pragma once
class SpriteScene : public Scene
{
public:
	SpriteScene();
	~SpriteScene();
	
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
private:
	shared_ptr<Sprite> _sprite;
	int curFrameX = 0;
	int curFrameY = 0;
};

