#pragma once
class Zelda
{
public:
	enum State
	{
		FRONT_IDLE,
		LEFT_IDLE,
		BACK_IDLE,
		RIGHT_IDLE,
		FRONT_RUN,
		LEFT_RUN,
		BACK_RUN,
		RIGHT_RUN
	};
	
	Zelda();
	~Zelda();

	void Update();
	void Render();

	void SetAction(State state);
	void SetPos(Vector2 pos);

private:
	void CreateAction();

	shared_ptr<Sprite> _sprite;
	vector<shared_ptr<Action>> _actions;

	State _state = State::FRONT_IDLE;

	shared_ptr<Action> _oldAction;
	shared_ptr<Action> _curAction;

	float _speed = 300.0f;
};

