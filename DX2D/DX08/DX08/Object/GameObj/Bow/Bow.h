#pragma once
class Bow
{
public:
	Bow(wstring path);
	~Bow();

	void Update();
	void Render();

	void SetParent(shared_ptr<Transform> transform) { _quad->GetTransform()->SetParent(transform); }
	shared_ptr<Transform> GetVirtualTransform() { return _virtual; }
	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }

	void SetPos(Vector2 pos);
	void SetScale(Vector2 scale);

	Vector2 GetPos();

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _virtual;
};

