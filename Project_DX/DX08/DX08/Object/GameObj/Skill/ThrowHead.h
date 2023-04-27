#pragma once
class ThrowHead : public Skill
{
public:
	ThrowHead();
	virtual ~ThrowHead();

	virtual void Update();
	virtual void Render();

	virtual void SetActive();

	virtual void Hit();
	void DeActivate();
	void SetEndEvent(function<void(void)> event) { _endEvent = event; }

	const shared_ptr<CircleCollider>& GetCollider() { return _col; }
private:
	shared_ptr<Quad> _quad;
	shared_ptr<CircleCollider> _col;

	float _speed = 1000.0f;

	function<void(void)> _endEvent;
};

