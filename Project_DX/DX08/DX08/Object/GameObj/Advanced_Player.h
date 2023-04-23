#pragma once
class Advanced_Player : public Player
{
public:
	Advanced_Player();
	~Advanced_Player();

	virtual void Update() override;
	virtual void Render() override;
	void PostRender();

	void EnAble();
	void DisAble();

	void Flip();
	void Move();
	void Jump();
	void Bungee();
	void Dash();
	void Fall();

	void Ground();
	void Bounce();

	void Attack();
	void AttackHit();
	void Skill();
	void HeadHit();
	void SkillHit();
	void Damaged(int damage, Direction dir);
	void CastFireArrow();

	void Dead();
	void Revive();

	const float& GetCurHp() { return _curHp; }
	const float& GetMaxHp() { return _maxHp; }
	const float& GetJumpPower() { return _curJumpPower; }

	shared_ptr<CircleCollider> GetAttackCol() { return _attackCol; }
	float GetAttackDamage();

	shared_ptr<CircleCollider> GetProjCol() { return _projCol; }
	float GetProjDamage();

	shared_ptr<CircleCollider> GetSkillCol() { return _skillCol; }

	const bool& GetIsBungee() { return _isBungee; }

	void SetEquipStats(StatAttributes stats);

	void SwapSkul();

private:
	void SetIdle();
	void DashEnd();
	void AttackMid();
	void AttackEnd();
	void AttackColEnd();
	void FallEnd();
	void SkillEnd();
	void ActivateSkillCol();
	void DeactivateSkillCol();
	void SetCallback();

	void SetAction(State state);
	void SetSkul(SkulType skulType);

	shared_ptr<CircleCollider> _attackCol;
	shared_ptr<CircleCollider> _skillCol;

	float _baseMaxHp = 100.0f;
	float _maxHp = _baseMaxHp;
	float _curHp = _baseMaxHp;

	UINT _baseDef = 0;
	UINT _def = _baseDef;

	float _baseScd = 5.0f;
	float _maxHeadDelay = _baseScd;
	float _headDelay = _baseScd;
	bool _isHeadOn = true;

	float _speed = 500.0f;

	float _maxInvincibleTime = 1.0f;
	float _curInvincibleTime = _maxInvincibleTime;
	bool _isInvincible = false;

	float _knockBackPower = 0.0f;
	bool _isKnockBacked = false;
	bool _isKnockBackRight = false;

	float _maxJumpPower = 800.0f;
	float _curJumpPower = 0.0f;
	bool _isJump = false;
	bool _isDoubleJump = false;
	bool _isGround = false;

	float _maxBungeeCD = 0.2f;
	float _curBungeeCD = _maxBungeeCD;
	bool _isBungee = false;

	float _maxDashDistance = 200.0f;
	float _curDashDistance = _maxDashDistance;
	float _maxDashCD = 2.0f;
	vector<float> _curDashCD = vector<float>(2, _maxDashCD);
	vector<bool> _isDash = vector<bool>(2, false);
	bool _isDodge = false;

	float _maxComboDuration = 0.9f;
	float _curComboDuration = _maxComboDuration;
	bool _isAttackB = false;

	UINT _maxAttackDamage = 30;
	UINT _minAttackDamage = 20;
	
	UINT _baseCrp = 10;
	UINT _critPercent = _baseCrp;

	shared_ptr<Quad> _proj;
	shared_ptr<CircleCollider> _projCol;
	float _projSpeed = 800.0f;
	float _maxProjCD = _baseScd;
	float _curProjCD = _baseScd;
	bool _isSkillRight = true;
	bool _isSkillUsed = false;
	bool _isSecondSkillUsed = false;
	int _maxProjDamage = 70;
	int _minProjDamage = 50;

	float _baseCcd = 15.0f;
	float _maxChangeCD = _baseCcd;
	float _curChangeCD = _baseCcd;
	bool _isFirstSkul = true;
	
	ATTRIBUTE _attribute = 0;

	StatAttributes _statAttributes;

	shared_ptr<FireArrow> _fireArrow;

	shared_ptr<ReverseBuffer> _reverseBuffer;
};