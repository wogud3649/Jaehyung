#include "framework.h"
#include "Floor.h"

Floor::Floor()
{
	_floor = make_shared<Quad>(L"Resources/Texture/BackGround/floor.png");

	Vector2 colSize = _floor->GetSize();
	_col = make_shared<RectCollider>(Vector2(colSize.x,colSize.y * 0.8));

	_floor->GetTransform()->SetParent(_col->GetTransform());
}

Floor::~Floor()
{
}

void Floor::Update()
{
	_col->Update();

	_floor->Update();
}

void Floor::Render()
{
	_floor->Render();
	_col->Render();
}
