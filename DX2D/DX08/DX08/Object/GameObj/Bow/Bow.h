#pragma once
class Bow
{
public:
	Bow();
	~Bow();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }
	Vector2 GetPos() { return Vector2(_quad->GetTransform()->GetPos()); }
	vector<shared_ptr<Bow_Arrow>>& GetArrows() { return _arrows; }
	
	void SetTarget(shared_ptr<Bow_Monster> target);

	void Fire(Vector2 direction);

private:
	shared_ptr<Quad> _quad;

	vector<shared_ptr<Bow_Arrow>> _arrows;
	int _arrowSize = 30;
};

