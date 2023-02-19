#pragma once
class Player
{
public:
	enum SkulType
	{
		SKUL,
		HEADLESS,

		SkulTypeSize
	};

	enum State
	{
		IDLE,
		WALK,
		JUMP,
		DASH,
		ATTACKA,
		ATTACKB,
		SKILL,

		StateSize
	};

	Player();
	~Player();

	virtual void Update();
	virtual void Render();

	shared_ptr<CircleCollider> GetBodyCollider() { return _bodyCol; }

protected:
	void CreateAction(SkulType _skulType);
	void SetAction(State state);
	void SetSkul(SkulType skulType);

	State _curState = State::IDLE;
	State _oldState = State::IDLE;

	SkulType _curSkul = SkulType::SKUL;
	SkulType _oldSkul = SkulType::SKUL;

	shared_ptr<Transform> _transform;
	shared_ptr<CircleCollider> _bodyCol;

	vector<vector<shared_ptr<Sprite>>> _sprites;
	vector<vector<shared_ptr<Action>>> _actions;

	float _speed = 500.0f;
	float _maxJumpPower = 700.0f;
	float _curjumpPower = 0.0f;

	int _maxHp = 100;
	int _curHp = _maxHp;

	bool _isAlive = true;
	Direction _direction = Direction::RIGHT;
};

