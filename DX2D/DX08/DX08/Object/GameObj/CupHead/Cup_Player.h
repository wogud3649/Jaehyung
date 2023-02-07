#pragma once
class Cup_Player
{
public:
	enum State
	{
		CUP_IDLE,
		CUP_RUN,
		CUP_SHOT,
		CUP_JUMP
	};

	Cup_Player();
	~Cup_Player();

	virtual void Update();
	virtual void Render();

	void SetRight();
	void SetLeft();

	void Input();
	void Jump();

	void SetAction(State state);
	void SetIDLE();

	shared_ptr<Collider> GetCollider() { return _col; }

protected:
	void CreateAction(string name, Action::Type type);

	State _curState = CUP_IDLE;
	State _oldState = CUP_IDLE;

	shared_ptr<Transform> _transform;
	shared_ptr<Collider> _col;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	float _speed = 300.0f;
	float _jumpPower = 400.0f;

	bool _isRight = true;
	bool _isJump = false;
};

