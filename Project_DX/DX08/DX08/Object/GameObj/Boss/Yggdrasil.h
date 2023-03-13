#pragma once
class Yggdrasil
{
public:
	enum State
	{
		IDLE,
		FISTATTACKREADY,
		FISTATTACK,
		FISTATTACKAFTER,
		FISTATTACKEND
	};
	Yggdrasil();
	~Yggdrasil();

	void Update();
	void Render();
	void PostRender();

	void Damaged(int damage);

	void SetTarget(shared_ptr<Advanced_Player> player) { _player = player; }
	void SetOriginPos(Vector2 pos);
	
	shared_ptr<CircleCollider> GetHeadCollider() { return _headCol; }
	shared_ptr<Transform> GetTransform() { return _body->GetTransform(); }

private:
	void MakeShared();
	void SetParent();
	void Adjust();
	
	void FistAttackReady();
	void FistAttack();
	void FistAttackAfter();

	Vector2 SetLERP(Vector2 objPos, Vector2 targetPos, float speed);
	void SetIdle();
	void Idle();

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

	int _maxHp = 500.0f;
	int _curHp = _maxHp;

	Vector2 _attackPos = Vector2(0, 170);
	float _maxAttackDelay = 2.0f;
	float _curAttackDelay = _maxAttackDelay;

	State _curState = State::IDLE;
	bool _isRightHand = true;

	int _maxDamage = 15.0f;
	int _minDamage = 4.0f;

	weak_ptr<Advanced_Player> _player;
};