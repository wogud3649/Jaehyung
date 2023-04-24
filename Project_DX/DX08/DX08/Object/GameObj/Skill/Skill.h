#pragma once
class Skill
{
public:
	Skill();
	virtual ~Skill();

	virtual void Update();
	virtual void Render();

	void SetPos(Vector2 pos) { _transform->SetPos(pos); }

	const float& GetPower() { return _power; }

protected:
	shared_ptr<Transform> _transform;

	float _power = 50.0f;
	float _maxDuration = 3.0f;
	float _curDuration = _maxDuration;
	bool _isRight = true;
};

