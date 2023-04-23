#pragma once
class Yggdrasil
{
public:
	enum AttackType
	{
		STAMP,
		SWEEP
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
	void HandRender();

	void Damaged(int damage);
	void Dead();

	void SetOriginPos(Vector2 pos);
	
	shared_ptr<CircleCollider> GetHeadCollider() { return _headCol; }
	shared_ptr<Transform> GetTransform() { return _body->GetTransform(); }
	float GetHpRatio() { return static_cast<float>(_curHp) / static_cast<float>(_maxHp); }

	const bool& GetAlive() { return _isAlive; }
	const float& GetDeadDelay() { return _deadDelay; }

	void Activate();
private:
	void MakeShared();
	void SetParent();
	void Adjust();
	void SetEffect();
	void SetCallBack();

	void Hit();
	
	void StampAttackReady();
	void StampAttack();
	void StampAttackAfter();

	void SpikeAttack();
	void SpikeFlipDir();
	void SpikeStop();

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

	shared_ptr<FilterBuffer> _filterBuffer;
	shared_ptr<ColorBuffer> _colorBuffer;

	shared_ptr<Quad> _rightHand;
	Vector2 _originRightHandPos;
	shared_ptr<Quad> _leftHand;
	Vector2 _originLeftHandPos;

	shared_ptr<CircleCollider> _headCol;
	shared_ptr<RectCollider> _rightBranchCol;
	shared_ptr<RectCollider> _leftBranchCol;
	shared_ptr<RectCollider> _rightHandCol;
	shared_ptr<RectCollider> _leftHandCol;

	int _maxHp = 50;
	int _curHp = _maxHp;
	bool _isAlive = true;

	Vector2 _attackPos = Vector2(0, 170);
	Vector2 _spikePos = Vector2(0, 170);
	float _maxAttackDelay = 2.0f;
	float _curAttackDelay = _maxAttackDelay;

	State _curState = State::IDLE;
	bool _isRightHand = true;

	int _maxDamage = 15;
	int _minDamage = 4;

	AttackType _attackType = AttackType::STAMP;

	shared_ptr<RectCollider> _spikeCol;
	float _maxSpikeDelay = 0.5f;
	float _curSpikeDelay = _maxSpikeDelay;
	bool _spikeReady = false;
	bool _spikeActive = false;
	bool _spikeUp = true;

	float _deadDelay = 3.0f;
};