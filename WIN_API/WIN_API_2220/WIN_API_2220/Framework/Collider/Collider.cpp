#include "framework.h"
#include "Collider.h"

Collider::Collider()
: _type(Type::NONE)
{
    _pens.reserve(3);
    HPEN red = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
    HPEN green = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
    HPEN blue = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));

    _pens.push_back(red);
    _pens.push_back(green);
    _pens.push_back(blue);

    _curPen = _pens[1];
}

Collider::~Collider()
{
    for (auto pen : _pens)
    {
        DeleteObject(pen);
    }
}

bool Collider::IsCollision(shared_ptr<Collider> col)
{
    if (_isActive == false)
        return false;
    // col이 circle인지 , rect인지 판단
    Type t = col->_type;
    switch (t)
    {
    case Collider::Type::NONE:
        break;
    case Collider::Type::CIRCLE:
        return IsCollision(dynamic_pointer_cast<CircleCollider>(col));
        break;
    case Collider::Type::RECT:
        return IsCollision(dynamic_pointer_cast<RectCollider>(col));
        break;
    default:
        break;
    }

    return false;
}
