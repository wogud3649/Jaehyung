#pragma once
class Skill
{
public:
	Skill();
	virtual ~Skill();

	virtual void Update();
	virtual void Render();

	void SetPos(Vector2 pos) { _transform->SetPos(pos); }
	void SetRight(bool isRight);
	virtual void SetActive();

	const float& GetPower() { return _power; }

protected:
	shared_ptr<Transform> _transform;

	float _power = 50.0f;
	float _maxDuration = 3.0f;
	float _curDuration = _maxDuration;

	shared_ptr<ReverseBuffer> _reverseBuffer;
	bool _isRight = true;

	bool _isActive = false;
};

