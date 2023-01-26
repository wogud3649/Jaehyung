#pragma once
class Bow
{
public:
	Bow();
	~Bow();

	void Update();
	void Render();

	void SetParent(shared_ptr<Transform> transform) { _quad->GetTransform()->SetParent(transform); }

	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }
	Vector2 GetPos() { return Vector2(_quad->GetTransform()->GetPos()); }
	vector<shared_ptr<Arrow>>& GetArrows() { return _arrows; }

	void Fire(Vector2 direction);

private:
	shared_ptr<Quad> _quad;

	vector<shared_ptr<Arrow>> _arrows;
	int _arrowSize = 30;
};

