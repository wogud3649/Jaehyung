#pragma once
class Inventory
{
public:
	Inventory();
	~Inventory();

	void Update();
	void Render();

	void SetPannelPos(Vector2 pos) { _pannel->GetTransform()->SetPos(pos); }

private:
	shared_ptr<Quad> _pannel;

	Vector2 _slotOffset;
	vector<shared_ptr<Slot>> _slots;
	vector<ItemInfo> _info;
};

