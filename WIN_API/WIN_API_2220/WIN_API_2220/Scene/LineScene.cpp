#include "framework.h"
#include "LineScene.h"

LineScene::LineScene()
{
	_line1 = make_shared<Line>();
	_line1->_startPos = Vector2(CENTER_X + 300, CENTER_Y - 200);
	_line2 = make_shared<Line>();
	_line2->_startPos = { 200,200 };
	_line2->_endPos = { 800,500 };

	_circle = make_shared<CircleCollider>(Vector2(CENTER_X, CENTER_Y), 5);
}

LineScene::~LineScene()
{
}

void LineScene::Update()
{
	_line1->_endPos = mousePos;

	Line::Result result = _line1->IsCollision(_line2);
	if (result.isCollision)
	{
		_circle->GetCenter() = result.contact;
		_line1->SetRed();
		_line2->SetRed();
		
	}
	else
	{
		_line1->SetGreen();
		_line2->SetGreen();
	}

	_line1->Update();
	_line2->Update();
	_circle->Update();
}

void LineScene::Render(HDC hdc)
{
	_line1->Render(hdc);
	_line2->Render(hdc);
	_circle->Render(hdc);
}
