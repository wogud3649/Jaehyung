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
private:
	shared_ptr<Quad> _quad;
};

