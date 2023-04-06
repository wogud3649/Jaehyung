#pragma once
class Chest : public InteractObj
{
public:
	Chest();
	virtual ~Chest();
	
	virtual void Update();
	virtual void Render();

private:
	virtual void CreateAction();

	void SetActive();

	Rarity _rarity;
};

