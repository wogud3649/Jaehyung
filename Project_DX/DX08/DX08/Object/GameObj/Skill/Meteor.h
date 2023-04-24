#pragma once
class Meteor : public Skill
{
public:
	Meteor();
	virtual ~Meteor();

	virtual void Update();
	virtual void Render();

	virtual void SetActive();
	void SetRandomSpeeds();

	virtual void Hit();
	virtual void DeActivate();

	const vector<shared_ptr<CircleCollider>>& GetColliders() { return _cols; }

private:
	vector<shared_ptr<Quad>> _quads;
	vector<shared_ptr<CircleCollider>> _cols;

	vector<float> _speeds = vector<float>(3, 0);

	float _maxJumpPower = 1000.0f;
	float _curJumpPower = _maxJumpPower;
};