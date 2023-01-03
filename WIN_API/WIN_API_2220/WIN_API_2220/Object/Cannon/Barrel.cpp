#include "framework.h"
#include "Barrel.h"

Barrel::Barrel()
{
	_line = make_shared<Line>();
}

Barrel::~Barrel()
{
}

void Barrel::Update()
{
	_line->Update();
}

void Barrel::Render(HDC hdc)
{
	_line->Render(hdc);
}

Vector2& Barrel::GetStart()
{
	return _line->_startPos;
}

Vector2& Barrel::GetEnd()
{
	return _line->_endPos;
}