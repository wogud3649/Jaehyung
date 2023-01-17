#pragma once
class Arrow
{
public:
	Arrow(wstring path);
	~Arrow();

	void Update();
	void Render();

	void SetParent(shared_ptr<Transform> transform) { _quad->GetTransform()->SetParent(transform); }
	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }

	void SetPos(Vector2 pos) { _quad->GetTransform()->GetPos() = pos; }
	void SetScale(Vector2 scale) { _quad->GetTransform()->GetScale() = scale; }
	void SetActive(bool active) { _isActive = active; }

	Vector2 GetPos() { return Vector2(_quad->GetTransform()->GetPos()); }
	bool GetActive() { return _isActive; }

private:
	shared_ptr<Quad> _quad;
	int count;
	bool _isActive = false;
};

