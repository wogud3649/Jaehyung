#pragma once
class ItemIcon
{
public:
	ItemIcon();
	~ItemIcon();

	void Update();
	void Render();

	void SetPos(Vector2 pos) { _sprite->GetTransform()->SetPos(pos); }
	void SetScale(Vector2 scale) { _sprite->GetTransform()->SetScale(scale); }
	void SetItem(const ItemInfo& info) { _sprite->SetCurFrame(Vector2(info.frameX, info.frameY)); }

private:
	shared_ptr<Sprite> _sprite;
	shared_ptr<Button> _button;
};

