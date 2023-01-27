#pragma once
class MyGameScene : public Scene
{
public:
	MyGameScene();
	~MyGameScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender();
private:
};

