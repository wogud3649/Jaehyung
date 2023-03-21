#pragma once
class MushroomEnt
{
public:
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

	void SetPlayer(shared_ptr<Advanced_Player> player) { _player = player; }

	const shared_ptr<CircleCollider>& GetStandBodyCol() { return _standBodyCol; }
	const shared_ptr<CircleCollider>& GetDuckBodyCol() { return _duckBodyCol; }
	const shared_ptr<RectCollider>& GetHeadCol() { return _headCol; }

private:
	void Function();
	void Collision();

	void Flip();
	void CreateAction();

	void SetColliders();
	void SetSprites();
	void SetCallback();
	void SetAction(State state);

	void SetIdle();
	void Duck();
	void StandEnd();
	void DuckEnd();

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<RectCollider> _headCol;
	shared_ptr<CircleCollider> _standBodyCol;
	shared_ptr<CircleCollider> _duckBodyCol;

	State _curState = State::IDLE;
	State _oldState = _curState;

	Direction _direction = Direction::RIGHT;

	bool _isDuck = false;
	bool _isAction = false;

	weak_ptr<Advanced_Player> _player;
};

