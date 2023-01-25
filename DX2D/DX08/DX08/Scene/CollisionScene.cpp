#include "framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	_rect = make_shared<RectCollider>(Vector2(100, 100));
	_rect->GetTransform()->GetPos() = Vector2(CENTER_X + 100, CENTER_Y);
	
	_rect2 = make_shared<RectCollider>(Vector2(100, 100));
	_rect2->GetTransform()->GetPos() = Vector2(CENTER_X - 100, CENTER_Y);

	_circle = make_shared<CircleCollider>(50.0f);
	_circle->GetTransform()->GetPos() = Vector2(CENTER_X+200, CENTER_Y+100);

	//_circle2 = make_shared<CircleCollider>(70.0f);
	//_circle2->GetTransform()->SetParent(_rect->GetTransform());
}

CollisionScene::~CollisionScene()
{
}

void CollisionScene::Update()
{
	if (KEY_DOWN(VK_UP))
	{
		_rect->GetTransform()->GetAngle() += 2 * PI / 360;
	}

	_rect->Update();
	_rect2->Update();
	_circle->Update();
	//_circle2->Update();

	if (_rect->IsCollision(_rect2))
	{
		_rect->SetRed();
		_rect2->SetRed();
	}
	else
	{
		_rect->SetGreen();
		_rect2->SetGreen();
	}

	if (_rect->IsCollision(_circle))
	{
		_rect->SetRed();
		_circle->SetRed();
	}
	else
	{
		_rect->SetGreen();
		_circle->SetGreen();
	}
	//if (_circle->IsCollision(_circle2))
	//{
	//	_circle->SetRed();
	//	_circle2->SetRed();
	//}
	//else
	//{
	//	_circle->SetGreen();
	//	_circle2->SetGreen();
	//}
}

void CollisionScene::Render()
{
	_rect->Render();
	_rect2->Render();
	_circle->Render();
	//_circle2->Render();
}

void CollisionScene::PostRender()
{
	ImGui::SliderFloat2("Rect Pos", (float*)&_rect->GetTransform()->GetPos(), 0, WIN_WIDTH);
	ImGui::SliderFloat2("Rect2 Pos", (float*)&_rect2->GetTransform()->GetPos(), 0, WIN_WIDTH);
	ImGui::SliderFloat2("Circle1 Pos", (float*)&_circle->GetTransform()->GetPos(), 0, WIN_WIDTH);
	//ImGui::SliderFloat2("Circle2 Pos", (float*)&_circle2->GetTransform()->GetPos(), 0, WIN_WIDTH);

	float circle_scale = _circle->GetTransform()->GetScale().x;
	ImGui::SliderFloat("Circle Scale", (float*)&circle_scale, 0, 3);
	_circle->GetTransform()->GetScale() = Vector2(circle_scale, circle_scale);

	//float circle2_scale = _circle2->GetTransform()->GetScale().x;
	//ImGui::SliderFloat("Circle2 Scale", (float*)&circle2_scale, 0, 3);
	//_circle2->GetTransform()->GetScale() = Vector2(circle2_scale, circle2_scale);

	float rect_scale = _rect->GetTransform()->GetScale().x;
	ImGui::SliderFloat("Rect Scale", (float*)&rect_scale, 0, 3);
	_rect->GetTransform()->GetScale() = Vector2(rect_scale, rect_scale);
	ImGui::SliderFloat("Rect Angle", (float*)&_rect->GetTransform()->GetAngle(), 0, PI*2);

	float rect2_scale = _rect2->GetTransform()->GetScale().x;
	ImGui::SliderFloat("Rect2 Scale", (float*)&rect2_scale, 0, 3);
	_rect2->GetTransform()->GetScale() = Vector2(rect2_scale, rect2_scale);
	ImGui::SliderFloat("Rect2 Angle", (float*)&_rect2->GetTransform()->GetAngle(), 0, PI*2);
	
}
