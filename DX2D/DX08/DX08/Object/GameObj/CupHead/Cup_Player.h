#pragma once
class Cup_Player
{
public:
	enum State
	{
		CUP_IDLE,
		CUP_RUN,
		CUP_JUMP,
		CUP_DUCK,
		CUP_DUCK_IDLE,
		CUP_AIM_STRAIGHT_SHOT
	};
	enum Direction
	{
		RIGHT,
		LEFT
	};

	Cup_Player();
	~Cup_Player();

	void Update();
	void Render();

	void Input();
	void Jump();
	void Shot();

	void SetRight();
	void SetLeft();

	void SetAction(State state);
	void SetAction(State state, Action::Type type);
	void SetIDLE();

	shared_ptr<Transform> GetTransform();

private:
	void CreatePath();
	void CreateSprite(int w, int h, int index);
	void CreateAction();
	void SetActionPos();
	void SetReverse(Direction direction);

	void Movement();

	vector<wstring> _spritePaths;
	vector<string> _xmlPaths;

	shared_ptr<Transform> _transform;
	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	State _state = State::CUP_IDLE;
	State _curState = State::CUP_IDLE;
	State _oldState = State::CUP_IDLE;

	Direction _dir = Direction::RIGHT;

	float _speed = 300.0f;
	float _jumpSpeed = 1000.0f;

	bool _isJump = false;
	bool _isDuck = false;
};

