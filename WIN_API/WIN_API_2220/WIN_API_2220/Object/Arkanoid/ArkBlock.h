#pragma once
class ArkBlock
{
public:
	ArkBlock();
	~ArkBlock();

	void Update();
	void Render(HDC hdc);

	shared_ptr<RectCollider>& GetCollider() { return _rect; }
	Vector2 Getsize() { return _size; }
	Vector2& GetCenter() { return _rect->GetCenter(); }
	bool& GetActive() { return _rect->_isActive; }

private:
	shared_ptr<RectCollider> _rect;
	Vector2 _size = { 125, 40 };
};