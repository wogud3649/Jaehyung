#include "framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
	circle = make_shared<CircleCollider>(50);
	circle->GetTransform()->SetPos(CENTER);
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	circle->Update();
}

void TestScene::Render()
{
	circle->Render();
}
