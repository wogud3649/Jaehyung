#pragma once
//TODO 발자취 추가 FOOTPRINT
class Block
{
public:
	enum class Type
	{
		NONE,
		ABLE,
		DISABLE,
		START,
		END,
		PLAYER,
		FOOTPRINT,
		SEARCHPRINT
	};

	Block();
	~Block();

	void Update();
	void Render(HDC hdc);

	void SetPosition(Vector2 pos) { _rect->GetCenter() = pos; }

	void SetType(Type type) { _type = type; }
	Type GetType() { return _type; }

private:
	Type _type = Type::NONE;

	vector<HBRUSH> _brushes;
	shared_ptr<RectCollider> _rect;
};