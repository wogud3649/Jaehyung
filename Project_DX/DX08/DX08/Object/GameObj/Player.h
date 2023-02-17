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
		WALK,
		JUMP,
		DASH,
		ATTACKA,
		SKILL,

		StateSize
	};

	Player();
	~Player();

	virtual void Update();
	virtual void Render();

	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }

protected:
	void CreateAction(string skulType);
	void SetAction(State state);

	State _curState = State::IDLE;
	State _oldState = State::IDLE;

	SkulType _skulType = SkulType::SKUL;

	shared_ptr<Transform> _transform;
	shared_ptr<CircleCollider> _col;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	float _speed = 500.0f;
	float _maxJumpPower = 700.0f;
	float _curjumpPower = 0.0f;

	int _maxHp = 100;
	int _curHp = _maxHp;

	bool _isAlive = true;
};

