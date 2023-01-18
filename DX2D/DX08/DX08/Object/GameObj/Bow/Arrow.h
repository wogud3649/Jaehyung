#pragma once
class Arrow
{
public:
	Arrow();
	~Arrow();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }

	void SetScale(Vector2 scale) { _quad->GetTransform()->GetScale() = scale; }
	void SetAngle(float angle) { _quad->GetTransform()->SetAngle(angle); }
	void SetPos(Vector2 pos) { _quad->GetTransform()->GetPos() = pos; }
	void SetActive(bool active) { _isActive = active; }
	void SetDirection(Vector2 dir);

	Vector2 GetPos() { return Vector2(_quad->GetTransform()->GetPos()); }
	bool GetActive() { return _isActive; }

private:
	shared_ptr<Quad> _quad;

	Vector2 _dir = { 0,0 };
	float _speed = 500.0f;
	double _duration = 0.0;
	bool _isActive = false;
};

