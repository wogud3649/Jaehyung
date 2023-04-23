#pragma once
class FireArrow
{
public:
	FireArrow();
	~FireArrow();

	void Update();
	void Render();

	void SetActive() { _isActive = true; }
	void SetPos(Vector2 pos) { _quad->GetTransform()->SetPos(pos); }
	void SetRight(bool isRight);

private:
	shared_ptr<Quad> _quad;
	shared_ptr<CircleCollider> _col;
	shared_ptr<ReverseBuffer> _reverseBuffer;

	float _maxDuration = 3.0f;
	float _curDuration = _maxDuration;
	float _speed = 1000.0f;
	bool _isActive = false;
	bool _isRight = true;
};