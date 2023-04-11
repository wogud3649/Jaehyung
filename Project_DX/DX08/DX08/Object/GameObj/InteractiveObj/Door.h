#pragma once
class Door : public InteractObj
{
public:
	enum DoorType
	{
		NORMAL,
		ITEM,
		SKULL,
		ADVANTURER,
		STORE,
		BOSS
	};

	Door();
	virtual ~Door();

	virtual void Update();
	virtual void Render();

	virtual void Activate();

	const shared_ptr<Transform>& GetTransform() { return _sprites[0]->GetTransform(); }

private:
	virtual void CreateAction();

	void Enter();

	DoorType _doorType;
};