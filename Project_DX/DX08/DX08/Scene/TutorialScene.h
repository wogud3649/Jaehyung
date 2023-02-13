#pragma once
class TutorialScene : public Scene
{
public:
	TutorialScene();
	~TutorialScene();
	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
private:
};

