#pragma once
class MushroomEnt : public Creature
{
public:
	enum DetectState
	{
		NONE,
		FIND
	};

	enum State
	{
		IDLE,
		WALK,
		ATTACK,
		DUCK,
		DUCKIDLE,
		DUCKWALK,
		DUCKATTACK,
		STAND
	};
	MushroomEnt();
	virtual ~MushroomEnt();

	virtual void Update() override;
	virtual void Render() override;
	void PostRender();

	void Ground();
	void Damaged(int damage);
	void Dead();
	void Duck();
	void Flip(Direction dir);

	void SetPos(Vector2 pos) { _standBodyCol->GetTransform()->SetPos(pos); }
	void SetEdge(Direction dir);

	const shared_ptr<CircleCollider>& GetStandBodyCol() { return _standBodyCol; }
	const shared_ptr<CircleCollider>& GetDuckBodyCol() { return _duckBodyCol; }
	const shared_ptr<RectCollider>& GetHeadCol() { return _headCol; }

	bool GetAlive() { return _isAlive; }

private:
	void Function();
	void Collision();

	void CreateAction();

	void SetColliders();
	void SetSprites();
	void SetCallback();
	void SetAction(State state);

	void SetIdle();
	void Walk();
	bool Stand();

	void Fall();
	
	void Detect();
	void Move();
	void Attack();

	void AttackMid();

	void StandEnd();
	void DuckEnd();
	void AttackEnd();

	void AttackColEnd();

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<RectCollider> _headCol;
	shared_ptr<CircleCollider> _standBodyCol;
	shared_ptr<CircleCollider> _duckBodyCol;

	shared_ptr<RectCollider> _detectCol;

	shared_ptr<CircleCollider> _attackCol;
	
	State _curState = State::IDLE;
	State _oldState = _curState;

	Direction _direction = Direction::RIGHT;

	float _maxIdleDuration = 3.0f;
	float _curIdleDuration = _maxIdleDuration;

	float _damagedDelay = 0.1f;
	bool _isDamaged = false;

	float _curJumpPower = 50.0f;
	float _moveSpeed = 80.0f;

	float _maxDuckDuration = 10.0f;
	float _curDuckDuration = _maxDuckDuration;
	bool _isDuck = false;
	bool _isAction = false;
	
	bool _isRightEdge = false;
	bool _isLeftEdge = false;

	shared_ptr<ColorBuffer> _colorBuffer;
};