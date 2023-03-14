#pragma once
class Yggdrasil
{
public:
	enum AttackType
	{
		STAMP,
		SWEEP,
		SHOOT
	};
	enum State
	{
		IDLE,
		ATTACKREADY,
		ATTACK,
		ATTACKAFTER,
		ATTACKEND
	};
	Yggdrasil();
	~Yggdrasil();

	void Update();
	void Render();
	void PostRender();

	void Damaged(int damage);
	void Dead();

	void SetTarget(shared_ptr<Advanced_Player> player) { _player = player; }
	void SetOriginPos(Vector2 pos);
	
	shared_ptr<CircleCollider> GetHeadCollider() { return _headCol; }
	shared_ptr<Transform> GetTransform() { return _body->GetTransform(); }

private:
	void MakeShared();
	void SetParent();
	void Adjust();
	
	void StampAttackReady();
	void StampAttack();
	void StampAttackAfter();

	void SweepAttackReady();
	void SweepAttack();
	void SweepAttackAfter();
	void SweepAttackEnd();

	Vector2 SetLERP(Vector2 objPos, Vector2 targetPos, float speed);
	float SetLERP(float start, float end, float speed);
	void SetIdle();
	void Idle();

	void DeActivate();

	shared_ptr<Quad> _body;
	Vector2 _originBodyPos;
	bool _up = true;

	shared_ptr<Quad> _rightHand;
	Vector2 _originRightHandPos;
	shared_ptr<Quad> _leftHand;
	Vector2 _originLeftHandPos;

	shared_ptr<CircleCollider> _headCol;
	shared_ptr<RectCollider> _rightBranchCol;
	shared_ptr<RectCollider> _leftBranchCol;
	shared_ptr<RectCollider> _rightHandCol;
	shared_ptr<RectCollider> _leftHandCol;

	int _maxHp = 500;
	int _curHp = _maxHp;
	bool _isAlive = true;

	Vector2 _attackPos = Vector2(0, 170);
	float _maxAttackDelay = 2.0f;
	float _curAttackDelay = _maxAttackDelay;

	State _curState = State::IDLE;
	bool _isRightHand = true;

	int _maxDamage = 15;
	int _minDamage = 4;

	weak_ptr<Advanced_Player> _player;

	AttackType _attackType = AttackType::SWEEP;
};