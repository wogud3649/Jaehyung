#pragma once
class UIScene : public Scene
{
public:
	UIScene();
	~UIScene();

	virtual void Update() override;
	virtual void Render() override;
private:
};

