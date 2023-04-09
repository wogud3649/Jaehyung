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
	void PlayAndMove();
	void End();

	void SetLeftRight(bool isRight);
	void SetActive(bool active);
	bool IsActive() { return _isActive; }

	void SetMidCallBack(function<void(void)> event, UINT index) { _action->SetMidCallBack(event, index); }
	void SetCallBack(function<void(void)> event) { _action->SetCallBack(event); }

	void SetParent(shared_ptr<Transform> parent) { _sprite->GetTransform()->SetParent(parent); }

private:
	void CreateAction(wstring file, Vector2 maxFrame, Vector2 size, float speed = 0.1f, Action::Type type = Action::Type::END);

	bool _isActive;

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;
};