#include "framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	_circle1 = make_shared<CircleCollider>(Vector2(CENTER_X - 300, CENTER_Y), 40);
	_circle2 = make_shared<CircleCollider>(Vector2(CENTER_X + 300, CENTER_Y), 30);

	_rect1 = make_shared<RectCollider>(Vector2(CENTER_X - 300, CENTER_Y + 150), Vector2(80,80));
	_rect2 = make_shared<RectCollider>(Vector2(CENTER_X + 300, CENTER_Y + 150), Vector2(100,60));
}

CollisionScene::~CollisionScene()
{
}

void CollisionScene::Update()
{
	if (_circle1->IsCollision(_circle2))
		_circle1->SetRed();
	else
		_circle1->SetGreen();

	if (_rect1->IsCollision(_circle2))
		_rect1->SetRed();
	else
		_rect1->SetGreen();

	_circle2->GetCenter() = LERP(_circle2->GetCenter(), mousePos, 0.1f);

	_circle1->Update();
	_circle2->Update();
	_rect1->Update();
	_rect2->Update();
}

void CollisionScene::Render(HDC hdc)
{
	_circle1->Render(hdc);
	_circle2->Render(hdc);
	_rect1->Render(hdc);
	_rect2->Render(hdc);
}
