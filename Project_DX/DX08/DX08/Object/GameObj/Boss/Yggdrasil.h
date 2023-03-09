#pragma once
class Yggdrasil
{
public:
	Yggdrasil();
	~Yggdrasil();

	void Update();
	void Render();
	void PostRender();

	void SetTarget(shared_ptr<Advanced_Player> player) { _player = player; }
	void SetOriginPos(Vector2 pos);

	shared_ptr<Transform> GetTransform() { return _body->GetTransform(); }

private:
	void MakeShared();
	void SetParent();
	void Adjust();
	void Attack();

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

	float _maxHp = 1000.0f;
	float _curHp = _maxHp;

	Vector2 _attackPos = Vector2(0, 70);
	float _maxAttackCooldown = 2.0f;
	float _curAttackCooldown = _maxAttackCooldown;
	float _maxAfterAttackDelay = 2.0f;
	float _curAfterAttackDelay = _maxAfterAttackDelay;
	bool _isAttack = false;
	bool _isRightHand = true;

	float maxDamage = 15.0f;
	float minDamage = 4.0f;

	weak_ptr<Advanced_Player> _player;
};

