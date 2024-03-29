#pragma once
class Player : public Creature
{
public:
	enum SkulType
	{
		SKUL,
		HEADLESS,
		WAREWOLFN,
		WIZARDN,
		WAREWOLFR,
		WIZARDR,
		WAREWOLFU,
		WIZARDU,
		WAREWOLFL,
		WIZARDL,

		SkulTypeSize
	};

	enum State
	{
		IDLE,
		WALK,
		JUMP,
		DASH,
		FALL,
		FALLREPEAT,
		ATTACKA,
		ATTACKB,
		JUMPATTACK,
		SKILL,
		SKILL2,

		StateSize
	};

	Player();
	virtual ~Player();

	virtual void Update() override;
	virtual void Render() override;

	shared_ptr<CircleCollider> GetBodyCollider() { return _bodyCol; }
	shared_ptr<CircleCollider> GetFootCollider() { return _footCol; }

protected:
	void CreateAction(SkulType _skulType);

	State _curState = State::IDLE;
	State _oldState = State::IDLE;

	SkulType _curSkul = SkulType::SKUL;
	SkulType _oldSkul = SkulType::SKUL;

	shared_ptr<Transform> _transform;
	shared_ptr<CircleCollider> _footCol;
	shared_ptr<CircleCollider> _bodyCol;

	vector<vector<shared_ptr<Sprite>>> _sprites;
	vector<vector<shared_ptr<Action>>> _actions;

	Direction _direction = Direction::RIGHT;

	float _attackSpeed = 0.09f;
};

