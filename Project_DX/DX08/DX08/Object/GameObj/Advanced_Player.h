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
	void Skill();
	void SkillHit();
	void Damaged(int damage, Direction dir);

	void Dead();
	void Revive();

	const float& GetJumpPower() { return _curJumpPower; }

	shared_ptr<CircleCollider> GetAttackCol() { return _attackCol; }
	float GetAttackDamage() { return (rand() % (_maxAttackDamage - _minAttackDamage) + _minAttackDamage); }

	shared_ptr<CircleCollider> GetProjCol() { return _projCol; }
	float GetProjDamage() { return (rand() % (_maxProjDamage - _minProjDamage) + _minProjDamage); }

	const bool& GetIsBungee() { return _isBungee; }

private:
	void SetIdle();
	void DashEnd();
	void AttackMid();
	void AttackEnd();
	void AttackColEnd();
	void FallEnd();
	void SkillEnd();
	void SetCallback();

	void SetAction(State state);
	void SetSkul(SkulType skulType);

	shared_ptr<CircleCollider> _attackCol;

	float _headDelay = 5.0f;
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

	int _maxAttackDamage = 15.0f;
	int _minAttackDamage = 5.0f;

	shared_ptr<Quad> _proj;
	shared_ptr<CircleCollider> _projCol;
	float _projSpeed = 800.0f;
	float _maxProjCD = 3.0f;
	float _curProjCD = _maxProjCD;
	bool _isProjRight = true;
	bool _isProjFired = false;

	int _maxProjDamage = 50.0f;
	int _minProjDamage = 25.0;
	
	shared_ptr<ReverseBuffer> _reverseBuffer;
};

