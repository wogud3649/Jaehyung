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

	void AttackA();
	void Skill();
	void Damaged();

	void Dead();
	void Revive();

private:
	void SetIdle();
	void DashEnd();
	void AttackEnd();
	void SkillEnd();
	void SetCallback();

	float _headDelay = 5.0f;
	bool _headOn = true;

	float _speed = 500.0f;

	float _maxJumpPower = 700.0f;
	float _curJumpPower = 0.0f;
	bool _isJump = false;
	bool _isGround = false;

	float _maxDashDistance = 1000.0f;
	float _curDashDistance = _maxDashDistance;
	float _maxDashCD = 2.0f;
	float _curDashCD = _maxDashCD;
	bool _isDash = false;
	bool _dashAble = true;

	bool _isAttacking = false;
	bool _isAttackA = true;
};

