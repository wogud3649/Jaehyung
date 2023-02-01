#pragma once
class Cup_Player
{
public:
	Cup_Player();
	~Cup_Player();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransform() { return _sprite->GetTransform(); }

private:
	void CreateAction();

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;
};

