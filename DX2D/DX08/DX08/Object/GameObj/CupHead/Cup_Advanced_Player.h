#pragma once
class Cup_Advanced_Player : public Cup_Player
{
public:
	Cup_Advanced_Player();
	virtual ~Cup_Advanced_Player();

	virtual void Update() override;
	virtual void Render() override;

	void EnAble();
	void DisAble();

	void Shot();
	void EndShot();
	void Jump();
	void Ground();
	void Edge();
	void Falling();
	void Beat();
	
	void Damaged();
	void Damaged(float amount);
	void Death();
	void Revive();

	void SetTarget(shared_ptr<Cup_Monster> target);

private:
	shared_ptr<Cup_Bullet> SelectBullet();
	
	shared_ptr<Transform> _muzzle;

	vector<shared_ptr<Cup_Bullet>> _bullets;
	const int _poolCount = 30;
};

