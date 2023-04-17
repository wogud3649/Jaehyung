#pragma once
class Store
{
public:
	Store();
	~Store();

	void Update();
	void Render();

	void SetPlayer(shared_ptr<Advanced_Player> player) { _player = player; }

private:
	void Collision();
	void StoreSettings();
	void SetRandomItems();

	shared_ptr<Quad> _quad;
	vector<shared_ptr<RectCollider>> _cols;

	vector<shared_ptr<Sprite>> _items;
	vector<shared_ptr<CircleCollider>> _itemCols;
	vector<ItemInfo> _itemInfos;

	weak_ptr<Advanced_Player> _player;
};

