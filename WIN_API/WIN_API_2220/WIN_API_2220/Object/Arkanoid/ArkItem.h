#pragma once
class ArkItem
{
public:
	enum class Type
	{
		NONE,
		DUPLICATE,
		BOMB,
	};

	ArkItem(Vector2 pos);
	~ArkItem();

	void Update();
	void Render(HDC hdc);

	Vector2& GetCenter() { return _pos; }

private:
	shared_ptr<CircleCollider> _item;
	Type _type = Type::NONE;
	Vector2 _pos = { 0.0f,0.0f };
	float _radius = 10.0f;
};