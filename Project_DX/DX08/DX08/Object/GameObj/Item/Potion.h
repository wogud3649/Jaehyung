#pragma once
class Potion
{
public:
	Potion();
	~Potion();

	void Update();
	void Render();

	void Activate();
	void SetPos(Vector2 pos) { _quad->GetTransform()->SetPos(pos); }

private:
	void DeActivate();
	shared_ptr<Quad> _quad;
	shared_ptr<CircleCollider> _col;

	int _healValue = 20;
	bool _isActive = false;
};