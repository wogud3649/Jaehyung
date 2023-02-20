#include "framework.h"
#include "Background.h"

Background::Background()
{
	_background = make_shared<Quad>(L"Resources/Texture/BackGround/Background.png");
	_background->SetSize(Vector2(WIN_WIDTH, WIN_HEIGHT));

	for (int i = 0; i < _poolCountFloor; i++)
		_floors.emplace_back(make_shared<Floor>());
	for (auto floor : _floors)
		floor->GetCollider()->GetTransform()->SetParent(_background->GetTransform());

	_floors[0]->GetCollider()->GetTransform()->MoveY(-300);

	_floors[1]->GetCollider()->GetTransform()->MoveY(-300);
	_floors[1]->GetCollider()->GetTransform()->MoveX(512);
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
			HIT_RESULT result = floor->GetHIT_RESULT(_player.lock()->GetBodyCollider());
			if (result.isHit)
			{
				_player.lock()->Ground();
			}
		}
	}
}

void Background::Render()
{
	_background->Render();
	for (auto floor : _floors)
		floor->Render();
}
