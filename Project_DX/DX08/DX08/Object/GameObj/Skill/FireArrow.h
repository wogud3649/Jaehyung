#pragma once
class FireArrow : public Skill
{
public:
	FireArrow();
	virtual ~FireArrow();

	virtual void Update();
	virtual void Render();

	virtual void SetActive();
	void SetRight(bool isRight);

	virtual void Hit();
	virtual void DeActivate();

	const shared_ptr<CircleCollider>& GetCollider() { return _col; }

private:
	shared_ptr<Quad> _quad;
	shared_ptr<CircleCollider> _col;
	shared_ptr<ReverseBuffer> _reverseBuffer;
};