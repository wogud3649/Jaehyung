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

	Cup_Player();
	~Cup_Player();

	virtual void Update();
	virtual void Render();

	void SetRight();
	void SetLeft();

	void Input();
	void Jump();
	void Shot();

	void SetAction(State state);
	void SetIDLE();
	void SetDuckIDLE();

	shared_ptr<Transform> GetTransform() { return _transform; }

protected:
	void Init();
	void CreateAction(string name, Action::Type type);

	shared_ptr<Transform> _transform;
	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<Cup_Bullet>> _bullets;
	int bulletSize = 5;

	State _curState = State::CUP_IDLE;
	State _oldState = State::CUP_IDLE;

	float _floorHeight = 0.0f;
	float _speed = 300.0f;
	float _jumpSpeed = 1000.0f;
	int _dir = 0;

	bool _isJump = false;
	bool _isDuck = false;
	bool _isShooting = false;
	bool _isDucking = false;

	bool _isRight = true;
};

