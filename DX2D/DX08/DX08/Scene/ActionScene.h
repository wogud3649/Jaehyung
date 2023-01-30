#pragma once
class ActionScene : public Scene
{
public:
	ActionScene();
	~ActionScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void CreateAction();

	void SetCheck() { _check = 1; }

private:
	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;

	int _check = 0;
};

