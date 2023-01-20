#include "framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	_rect = make_shared<RectCollider>(Vector2(100, 100));
	_rect->GetTransform()->GetPos() = Vector2(CENTER_X, CENTER_Y);

	_circle = make_shared<CircleCollider>(50.0f);
	_circle->GetTransform()->GetPos() = Vector2(CENTER_X, CENTER_Y);
}

CollisionScene::~CollisionScene()
{
}

void CollisionScene::Update()
{
	//_rect->Update();
	_circle->Update();
}

void CollisionScene::Render()
{
	//_rect->Render();
	_circle->Render();
}
