#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2 _center, Vector2 size)
: size(size)
, Collider()
{
    this->_center = _center;
    _type = Collider::Type::RECT;
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
    if (_isActive == false)
        return;
}

void RectCollider::Render(HDC hdc)
{
    if (_isActive == false)
        return;

    SelectObject(hdc, _curPen);
	Rectangle(hdc, Left(), Top(), Right(), Bottom());
}

bool RectCollider::IsCollision(const Vector2& pos)
{
    if (_isActive == false)
        return false;

    if (pos.x <= Right() && pos.x >= Left())
    {
        if (pos.y <= Bottom() && pos.y >= Top())
            return true;
    }

    return false;
}

bool RectCollider::IsCollision(const shared_ptr<RectCollider> rect)
{
    if (Right() >= rect->Left() && Left() <= rect->Right())
    {
        if (Bottom() >= rect->Top() && Top() <= rect->Bottom())
            return true;
    }

    return false;
}

bool RectCollider::IsCollision(const shared_ptr<CircleCollider> circle)
{
    Vector2 leftTop = Vector2(Left(), Top());
    Vector2 rightTop = Vector2(Right(), Top());
    Vector2 leftBottom = Vector2(Left(), Bottom());
    Vector2 rightBottom = Vector2(Right(), Bottom());

    if (circle->IsCollision(leftTop) || circle->IsCollision(rightTop)
        || circle->IsCollision(leftBottom) || circle->IsCollision(rightBottom))
        return true;

    if (Right() >= circle->GetCenter().x && Left() <= circle->GetCenter().x)
    {
        if (Top() - circle->GetRadius() <= circle->GetCenter().y && Bottom() + circle->GetRadius() >= circle->GetCenter().y)
        {
            _vCollision = true;
            return true;
        }
    }

    if (Top() <= circle->GetCenter().y && Bottom() >= circle->GetCenter().y)
    {
        if (Left() - circle->GetRadius() <= circle->GetCenter().x && Right() + circle->GetRadius() >= circle->GetCenter().x)
        {
            _hCollision = true;
            return true;
        }
    }

    return false;
}
