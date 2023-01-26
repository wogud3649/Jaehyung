#include "framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	_rect = make_shared<RectCollider>(Vector2(100, 100));
	_rect->GetTransform()->GetPos() = Vector2(CENTER_X, CENTER_Y);

	_circle1 = make_shared<CircleCollider>(50);
	_circle1->GetTransform()->GetPos() = Vector2(CENTER_X + 200, CENTER_Y + 100);

	_rect2 = make_shared<RectCollider>(Vector2(50, 50));
	_rect2->GetTransform()->SetParent(_rect->GetTransform());
	_rect2->GetTransform()->GetPos() = Vector2(150, 150);
}

CollisionScene::~CollisionScene()
{
}

void CollisionScene::Update()
{
	_rect->Update();
	_circle1->Update();
	_rect2->Update();

	if (_rect2->IsCollision(_circle1, true))
	{
		_rect2->SetRed();
		_circle1->SetRed();
	}
	else
	{
		_rect2->SetGreen();
		_circle1->SetGreen();
	}
}

void CollisionScene::Render()
{
	_rect->Render();
	_circle1->Render();
	_rect2->Render();
}

void CollisionScene::PostRender()
{
	ImGui::SliderFloat2("Rect Pos", (float*)&_rect->GetTransform()->GetPos(), 0, WIN_WIDTH);
	ImGui::SliderFloat2("Circle1 Pos", (float*)&_circle1->GetTransform()->GetPos(), 0, WIN_WIDTH);
	ImGui::SliderFloat2("Circle2 Pos", (float*)&_rect2->GetTransform()->GetPos(), 0, WIN_WIDTH);
	ImGui::SliderFloat("RectAngle", &_rect->GetTransform()->GetAngle(), 0, 2 * PI);

	float circle2_scale = _rect2->GetTransform()->GetScale().x;
	ImGui::SliderFloat("Circle2 Scale", (float*)&circle2_scale, 0, 3);
	_rect2->GetTransform()->GetScale() = Vector2(circle2_scale, circle2_scale);

	float rect_Scale = _rect->GetTransform()->GetScale().x;
	ImGui::SliderFloat("Rect Scale", (float*)&rect_Scale, 0, 3);
	_rect->GetTransform()->GetScale() = Vector2(rect_Scale, rect_Scale);
}
