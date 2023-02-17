#include "framework.h"
#include "Background.h"

Background::Background()
{
	_background = make_shared<Quad>(L"Resources/Texture/BackGround/Background.png");

	for (int i = 0; i < _poolCountFloor; i++)
		_floors.emplace_back(make_shared<Floor>());
	for (auto floor : _floors)
		floor->GetCollider()->GetTransform()->SetParent(_background->GetTransform());

	_floors[0]->GetCollider()->GetTransform()->MoveY(-300);
}

Background::~Background()
{
}

void Background::Update()
{
	for (auto floor : _floors)
		floor->Update();
}

void Background::Render()
{
	for (auto floor : _floors)
		floor->Render();
}
