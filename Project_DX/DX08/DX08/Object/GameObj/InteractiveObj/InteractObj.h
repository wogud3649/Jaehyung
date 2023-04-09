#pragma once
class InteractObj
{
public:
	InteractObj();
	virtual ~InteractObj();
	
	virtual void Update();
	virtual void Render();

	void SetPlayer(shared_ptr<Advanced_Player> player) { _player = player; }

	void Spawn();
	void Extinct();
	virtual void Activate();
	virtual void DeActivate();

protected:
	virtual void CreateAction();

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<RectCollider> _col;

	bool _isSpawn = false;
	bool _isActive = false;

	weak_ptr<Advanced_Player> _player;
};