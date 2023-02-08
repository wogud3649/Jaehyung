#pragma once
class Cup_Advanced_Player : public Cup_Player
{
public:
	Cup_Advanced_Player();
	virtual ~Cup_Advanced_Player();

	virtual void Update() override;
	virtual void Render() override;

	void Shot();
	void EndShot();
	void Jump();
	void Ground();
	void Falling();
	void Beat();

	shared_ptr<Cup_Bullet> SelectBullet();

private:
	shared_ptr<Transform> _muzzle;

	vector<shared_ptr<Cup_Bullet>> _bullets;
	const int _poolCount = 30;
};

