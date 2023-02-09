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

	void SetAction(State state);
	void SetIDLE();

	int& GetHp() { return _curHp; }
	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<CircleCollider> GetBodyCollider() { return _col; }

protected:
	void CreateAction(string name, Action::Type type);

	State _curState = CUP_IDLE;
	State _oldState = CUP_IDLE;

	shared_ptr<Transform> _transform;
	shared_ptr<CircleCollider> _col;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	float _speed = 300.0f;
	float _maxJumpPower = 700.0f;
	float _jumpPower = 0.0f;

	int _maxHp = 3;
	int _curHp = _maxHp;
	
	bool isAlive = true;
	bool _isRight = true;
	bool _isJump = false;
	bool _isShooting = false;
};

