#include "framework.h"
#include "PaintScene.h"

PaintScene::PaintScene()
{
    _rect = make_shared<RectCollider>(Vector2(CENTER_X,CENTER_Y), Vector2(100,80));
    _circle = make_shared<CircleCollider>(Vector2(CENTER_X + 100, CENTER_Y), 30);

    _rect->SetRed();
}

PaintScene::~PaintScene()
{
}

void PaintScene::Update()
{
    _rect->Update();
    _circle->Update();
}

void PaintScene::Render(HDC hdc)
{
    _rect->Render(hdc);
    _circle->Render(hdc);

    // 선그리기
    // MoveToEx(hdc, 0, 0, nullptr);
    // LineTo(hdc, mousePos.x, mousePos.y);
}
