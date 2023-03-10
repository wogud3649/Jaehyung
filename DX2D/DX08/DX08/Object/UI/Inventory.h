#pragma once
class Inventory
{
public:
	Inventory();
	~Inventory();

	void Update();
	void Render();
	void PostRender();

	void SetPannelPos(Vector2 pos) { _pannel->GetTransform()->SetPos(pos); }

	void AddMoney(int money) { if (money > 0) return; _money += money; }

private:
	shared_ptr<Quad> _pannel;

	Vector2 _slotOffset;
	vector<shared_ptr<Slot>> _slots;
	vector<ItemInfo> _itemDatas;

	shared_ptr<ItemIcon> _icon;

	UINT _money = 0;
};

