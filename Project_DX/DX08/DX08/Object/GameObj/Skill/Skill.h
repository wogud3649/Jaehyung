#pragma once
class Skill
{
public:
	Skill();
	virtual ~Skill();

	virtual void Update();
	virtual void Render();

	virtual void SetActive();
	void SetPos(Vector2 pos) { _transform->SetPos(pos); }

	virtual void Hit();
	virtual void DeActivate();

	const float& GetPower() { return _power; }

protected:
	shared_ptr<Transform> _transform;

	float _power = 50.0f;
	float _maxDuration = 3.0f;
	float _curDuration = _maxDuration;
	float _speed = 1000.0f;
	bool _isActive = false;
	bool _isRight = true;
};

