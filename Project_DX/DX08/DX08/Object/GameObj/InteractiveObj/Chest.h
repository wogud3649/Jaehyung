#pragma once
class Chest : public InteractObj
{
public:
	Chest();
	virtual ~Chest();
	
	virtual void Update();
	virtual void Render();

	const shared_ptr<Transform>& GetTransform() { return _sprites[0][0]->GetTransform(); }

	virtual void Spawn();
	virtual void Extinct();
	void SetRandom();
private:
	virtual void CreateAction();

	void OpenChest();
	void ItemPop();

	void TakeItem();

	shared_ptr<Item> _item;

	Rarity _rarity = Rarity::NONE;

	float _popSpeed = 700.0f;
	bool _isOpen = false;

	float _itemActivateDelay = 1.2f;

	shared_ptr<Potion> _potion;
};