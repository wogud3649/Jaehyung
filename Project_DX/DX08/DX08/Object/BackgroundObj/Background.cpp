#include "framework.h"
#include "Background.h"

Background::Background()
{
	_sky = make_shared<Quad>(L"Resources/Texture/BackGround/BlueSky.png");
	_trees = make_shared<Quad>(L"Resources/Texture/BackGround/Forest.png");

	_sky->GetTransform()->SetPos(CENTER);
	_sky->GetTransform()->SetScale(Vector2(1.45f, 1.45f));

	_trees->GetTransform()->SetPos(CENTER);
	_trees->GetTransform()->SetScale(Vector2(1.4f, 1.4f));
	
	_trees->Update();
	_sky->Update();
}

Background::~Background()
{
}

void Background::Update()
{
}

void Background::BackgroundRender()
{
	_sky->Render();
	_trees->Render();
}