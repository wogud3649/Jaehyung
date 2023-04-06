#pragma once
class InteractObj
{
public:
	InteractObj();
	virtual ~InteractObj();
	
	virtual void Update();
	virtual void Render();

protected:
	virtual void CreateAction();

	virtual void SetActive();

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<RectCollider> _col;

	bool _isSpawn = false;
	bool _isActive = false;
};

