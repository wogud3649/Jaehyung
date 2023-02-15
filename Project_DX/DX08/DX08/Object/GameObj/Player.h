#pragma once
class Player
{
public:
	enum SkulType
	{
		SKUL,
		HEADLESS
	};

	enum State
	{
		IDLE,
		WALK
	};

	Player();
	~Player();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }

private:
	void CreateAction(SkulType skulType, State state, Action::Type type);
	void SetAction(State state);
	void Input();

	State _curState = State::IDLE;
	State _oldState = State::IDLE;

	SkulType _skulType = SkulType::SKUL;

	shared_ptr<Transform> _transform;
	shared_ptr<CircleCollider> _col;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	float _speed = 500.0f;
};

