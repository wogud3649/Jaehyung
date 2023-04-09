#pragma once
class Chest : public InteractObj
{
public:
	Chest();
	virtual ~Chest();
	
	virtual void Update();
	virtual void Render();

	const shared_ptr<Transform>& GetTransform() { return _sprites[0]->GetTransform(); }

	virtual void Activate();

private:
	virtual void CreateAction();

	void OpenChest();
	void ItemPop();

	void RandomNormal();
	void RandomRare();
	void RandomUnique();
	void RandomLegendary();

	shared_ptr<Sprite> _item;

	Rarity _rarity;

	float _popSpeed = 700.0f;
	bool _isOpen = false;
};