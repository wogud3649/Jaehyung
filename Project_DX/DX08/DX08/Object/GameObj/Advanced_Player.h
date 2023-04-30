#pragma once
class Advanced_Player : public Player
{
public:
	enum SkillType
	{
		NONE,
		MELEE,
		THROWHEAD,
		FIREARROW,
		METEOR
	};
	Advanced_Player();
	virtual ~Advanced_Player();

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
	void Skill2();
	void ThrowHeadHit();
	void FireArrowHit();
	void MeteorHit(int index);

	void CastThrowHead();
	void CastFireArrow();
	void CastMeteor();

	void Heal(int value);
	void Damaged(int damage, Direction dir);
	void Dead();
	void Revive();

	const float& GetCurHp() { return _curHp; }
	const float& GetMaxHp() { return _maxHp; }
	const float& GetJumpPower() { return _curJumpPower; }

	const shared_ptr<CircleCollider>& GetAttackCol() { return _attackCol; }
	const float& GetAttackDamage();

	const shared_ptr<CircleCollider>& GetThrowHeadCol() { return _throwHead->GetCollider(); }
	const shared_ptr<CircleCollider>& GetArrowCol() { return _fireArrow->GetCollider(); }
	const vector<shared_ptr<CircleCollider>>& GetMeteorCols() { return _meteor->GetColliders(); }
	const float& GetSkillDamage();

	const bool& GetIsBungee() { return _isBungee; }

	void SetEquipStats(StatAttributes stats);

	void SwapSkul();
	bool GetIsFirstSkul() { return _isFirstSkul; }

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
	
	UINT _baseCrp = 10;
	UINT _critPercent = _baseCrp;

	float _maxSkillCD = _baseScd;
	float _curSkillCD = _baseScd;
	bool _isSkillUsed = false;

	float _curSkill2CD = _baseScd;
	bool _isSkill2Used = false;

	float _baseCcd = 15.0f;
	float _maxChangeCD = _baseCcd;
	float _curChangeCD = _baseCcd;
	bool _isFirstSkul = true;
	
	ATTRIBUTE _attribute = 0;

	StatAttributes _statAttributes;

	SkillType _skillType = SkillType::NONE;
	shared_ptr<ThrowHead> _throwHead;
	shared_ptr<FireArrow> _fireArrow;
	shared_ptr<Meteor> _meteor;

	shared_ptr<ReverseBuffer> _reverseBuffer;
};