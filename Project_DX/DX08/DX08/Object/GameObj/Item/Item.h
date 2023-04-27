#pragma once
class Item
{
public:
	Item();
	~Item();

	void Update();
	void Render();

	void Activate();
	void DeActivate();

	void SetPos(Vector2 pos) { _item->GetTransform()->SetPos(pos); }
	void MoveY(float y) { _item->GetTransform()->MoveY(y); }
	void SetItem(int itemCode);

	const shared_ptr<CircleCollider>& GetCollider() { return _col; }
	const Vector2& GetPos() { return _item->GetTransform()->GetWorldPos(); }
	const int& GetItem() { return _itemInfo.itemCode; }
	const bool& GetActive() { return _isActive; }

private:
	shared_ptr<Sprite> _item;
	shared_ptr<CircleCollider> _col;
	ItemInfo _itemInfo;

	bool _isActive = false;
};

