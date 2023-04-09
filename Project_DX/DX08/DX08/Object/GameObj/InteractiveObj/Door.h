#pragma once
class Door : public InteractObj
{
public:
	enum DoorType
	{
		NORMAL,
		ITEM,
		SKULL,
		STORE,
		ADVANTURER,
		BOSS
	};

	Door();
	virtual ~Door();

	virtual void Update();
	virtual void Render();

	const shared_ptr<Transform>& GetTransform() { return _sprites[0]->GetTransform(); }

	virtual void Activate();

private:
	virtual void CreateAction();

	void Enter();

	DoorType _doorType;
};