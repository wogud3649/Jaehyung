#pragma once
class InteractObj
{
public:
	InteractObj();
	virtual ~InteractObj();
	
	virtual void Update();
	virtual void Render();

	virtual void Spawn();
	virtual void Extinct();
	virtual void Activate();
	void DeActivate();

protected:
	virtual void CreateAction();

	vector<vector<shared_ptr<Sprite>>> _sprites;
	vector<vector<shared_ptr<Action>>> _actions;

	shared_ptr<RectCollider> _col;

	UINT _selected = 0;

	bool _isSpawn = false;
	bool _isActive = false;
};