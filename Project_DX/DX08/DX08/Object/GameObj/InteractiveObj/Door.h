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
private:
	virtual void CreateAction();

	virtual void SetActive();

	DoorType _doorType;
};