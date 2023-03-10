#pragma once
class Slot
{
public:
	Slot();
	~Slot();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _quad->GetTransform()->SetPos(pos);}
	void SetParent(shared_ptr<Transform> transform) { _quad->GetTransform()->SetParent(transform); }

	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }
private:
	shared_ptr<Quad> _quad;
};

