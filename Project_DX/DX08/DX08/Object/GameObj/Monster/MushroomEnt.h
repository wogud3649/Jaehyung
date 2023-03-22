#pragma once
class MushroomEnt
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
	~MushroomEnt();

	void Update();
	void Render();

	void SetPos(Vector2 pos) { _standBodyCol->GetTransform()->SetPos(pos); }
	void SetPlayer(shared_ptr<Advanced_Player> player) { _player = player; }

	const shared_ptr<CircleCollider>& GetStandBodyCol() { return _standBodyCol; }
	const shared_ptr<CircleCollider>& GetDuckBodyCol() { return _duckBodyCol; }
	const shared_ptr<RectCollider>& GetHeadCol() { return _headCol; }

private:
	void Function();
	void Collision();

	void Flip(Direction dir);

	void CreateAction();

	void SetColliders();
	void SetSprites();
	void SetCallback();
	void SetAction(State state);

	void SetIdle();
	void Walk();
	void Duck();
	bool Stand();

	void Fall();
	
	void Detect();
	void Follow();
	void Attack();

	void AttackMid();

	void StandEnd();
	void DuckEnd();
	void AttackEnd();

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<RectCollider> _headCol;
	shared_ptr<CircleCollider> _standBodyCol;
	shared_ptr<CircleCollider> _duckBodyCol;

	shared_ptr<RectCollider> _detectCol;
	
	State _curState = State::IDLE;
	State _oldState = _curState;

	Direction _direction = Direction::RIGHT;

	weak_ptr<Advanced_Player> _player;

	float _curJumpPower = 0.0f;
	float _moveSpeed = 100.0f;

	float _maxDuckDuration = 10.0f;
	float _curDuckDuration = _maxDuckDuration;
	bool _isDuck = false;
	bool _isAction = false;
};