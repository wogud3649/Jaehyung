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

private:
	void SetIdle();

	float _dashTime = 5.0f;
	float _dashDelay;
};

