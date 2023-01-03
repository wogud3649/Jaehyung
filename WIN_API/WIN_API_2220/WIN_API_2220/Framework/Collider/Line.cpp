#include "framework.h"
#include "Line.h"

Line::Line()
{
    _pens.reserve(3);
    HPEN red = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    HPEN green = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
    HPEN blue = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

    _pens.push_back(red);
    _pens.push_back(green);
    _pens.push_back(blue);

    _curPen = _pens[1];
}

Line::~Line()
{
    for (auto pen : _pens)
    {
        DeleteObject(pen);
    }
}

void Line::Update()
{
}

void Line::Render(HDC hdc)
{
    SelectObject(hdc,_curPen);
    MoveToEx(hdc, _startPos.x, _startPos.y, nullptr);
    LineTo(hdc, _endPos.x, _endPos.y);
}

Line::Result Line::IsCollision(shared_ptr<Line> line)
{
    Result result;
    Vector2 a = _endPos - _startPos;
    Vector2 a1 = line->_startPos - _startPos;
    Vector2 a2 = line->_endPos - _startPos;

    bool between1 = a.IsBetween(a1, a2);

    Vector2 b = line->_endPos - line->_startPos;
    Vector2 b1 = _startPos - line->_startPos;
    Vector2 b2 = _endPos - line->_startPos;

    bool between2 = b.IsBetween(b1, b2);

    if (between1 & between2)
    {
        result.isCollision = true;
        float leftTriangle = abs(a.Cross(a1));
        float rightTriangle = abs(a.Cross(a2));

        float t = (leftTriangle / (leftTriangle + rightTriangle));
        result.contact = LERP(line->_startPos, line->_endPos, t);
    }

    return result;
}
