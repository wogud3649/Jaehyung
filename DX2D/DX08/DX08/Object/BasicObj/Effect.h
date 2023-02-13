#pragma once
class Effect
{
public:
	Effect(wstring file, Vector2 maxFrame, Vector2 size, float speed = 0.1f, Action::Type type = Action::Type::END);
	~Effect();

	void Update();
	void Render();
	void PostRender();
	
	void Play(Vector2 pos);
	void End();

	void SetActive(bool active);
	bool IsActive() { return _isActive; }

private:
	void CreateAction(wstring file, Vector2 maxFrame, Vector2 size, float speed = 0.1f, Action::Type type = Action::Type::END);
	
	bool _isActive;
	
	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;

	
};

