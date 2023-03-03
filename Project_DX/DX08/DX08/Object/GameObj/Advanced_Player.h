#pragma once
class Advanced_Player : public Player
{
public:
	Advanced_Player();
	~Advanced_Player();

	virtual void Update() override;
	virtual void Render() override;

	void EnAble();
	void DisAble();

	void Flip();
	void Move();
	void Jump();
	void Dash();
	void Fall();

	void Ground();
	void Beat();

	void Attack();
	void Skill();
	void Damaged();

	void Dead();
	void Revive();

	const float& GetJumpPower() { return _curJumpPower; }

private:
	void SetIdle();
	void DashEnd();
	void AttackEnd();
	void FallEnd();
	void SkillEnd();
	void SetCallback();

	void SetAction(State state);
	void SetSkul(SkulType skulType);

	float _headDelay = 5.0f;
	bool _headOn = true;

	float _speed = 500.0f;

	float _maxJumpPower = 1200.0f;
	float _curJumpPower = 0.0f;
	bool _isJump = false;
	bool _doubleJump = false;
	bool _isGround = false;

	float _maxDashDistance = 1500.0f;
	float _curDashDistance = _maxDashDistance;
	float _maxDashCD = 2.0f;
	vector<float> _curDashCD = vector<float>(2, _maxDashCD);
	vector<bool> _isDash = vector<bool>(2, false);

	float _maxComboDuration = 0.9f;
	float _curComboDuration = _maxComboDuration;
	bool _attackB = false;
};

