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
		STOREDOOR,
		BOSS,
		DOORTYPESIZE
	};

	Door();
	virtual ~Door();

	virtual void Update();
	virtual void Render();

	virtual void Activate();
	void SetRandom();

	const shared_ptr<Transform>& GetTransform() { return _sprites[0][0]->GetTransform(); }
	void SetCallBack(function<void(void)> event) { _endEvent = event; }

private:
	virtual void CreateAction();

	void Enter();

	DoorType _doorType;

	function<void(void)> _endEvent = nullptr;
};