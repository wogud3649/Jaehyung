#pragma once
class Bow
{
public:
	Bow(wstring path);
	~Bow();

	void Update();
	void Render();

	void SetParent(shared_ptr<Transform> transform) { _quad->GetTransform()->SetParent(transform); }
	vector<shared_ptr<Transform>> GetVirtualTransforms() { return _virtuals; }
	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }

	void SetPos(Vector2 pos);
	void SetScale(Vector2 scale);

	Vector2 GetPos() { return Vector2(_quad->GetTransform()->GetPos());}

private:
	shared_ptr<Quad> _quad;

	vector<shared_ptr<Transform>> _virtuals;
	int _virtualSize = 30;
};

