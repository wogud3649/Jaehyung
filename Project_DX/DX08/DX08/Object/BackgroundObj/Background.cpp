#include "framework.h"
#include "Background.h"

Background::Background()
{
	_background = make_shared<Quad>(L"Resources/Texture/BackGround/Background.png");
	_backgroundSize = _background->GetSize();

	for (int i = 0; i < _poolCountFloor; i++)
		_floors.emplace_back(make_shared<Floor>());
	for (auto floor : _floors)
		floor->GetCollider()->GetTransform()->SetParent(_background->GetTransform());

	float floorHeight = 80 - _backgroundSize.y * 0.5;

	_floors[0]->GetCollider()->GetTransform()->MoveY(floorHeight);
	_floors[0]->GetCollider()->GetTransform()->MoveX(-1024);

	_floors[1]->GetCollider()->GetTransform()->MoveY(floorHeight);
	_floors[1]->GetCollider()->GetTransform()->MoveX(-512);

	_floors[2]->GetCollider()->GetTransform()->MoveY(floorHeight);

	_floors[3]->GetCollider()->GetTransform()->MoveY(floorHeight);
	_floors[3]->GetCollider()->GetTransform()->MoveX(512);

	_floors[4]->GetCollider()->GetTransform()->MoveY(floorHeight);
	_floors[4]->GetCollider()->GetTransform()->MoveX(1024);

	_floors[5]->GetCollider()->GetTransform()->MoveY(floorHeight * 0.5);
}

Background::~Background()
{
}

void Background::Update()
{
	_background->Update();
	for (auto floor : _floors)
		floor->Update();

	if (_player.expired() == false)
	{
		for (auto floor : _floors)
		{
			HIT_RESULT result = floor->GetHIT_RESULT(_player.lock()->GetFootCollider());
			if (result.isHit == false)
				continue;

			if (result.dir == Direction::UP)
				_player.lock()->Ground();
			else if (result.dir == Direction::DOWN)
				_player.lock()->Beat();
		}
	}
}

void Background::Render()
{
	_background->Render();
	for (auto floor : _floors)
		floor->Render();
}

Vector2 Background::LeftBottom()
{
	Vector2 curPos = _background->GetTransform()->GetWorldPos();
	Vector2 size = _background->GetSize() * 0.5f;
	return (curPos - size);
}

Vector2 Background::RightTop()
{
	Vector2 curPos = _background->GetTransform()->GetWorldPos();
	Vector2 size = _background->GetSize() * 0.5f;
	return (curPos + size);
}
