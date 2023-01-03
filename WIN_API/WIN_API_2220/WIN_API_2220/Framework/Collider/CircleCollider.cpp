#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Vector2 _center, float radius)
: radius(radius)
, Collider()
{
    this->_center = _center;
    _type = Collider::Type::CIRCLE;
}

CircleCollider::~CircleCollider()
{

}

void CircleCollider::Update()
{
    if (_isActive == false)
        return;
}

void CircleCollider::Render(HDC hdc)
{
    if (_isActive == false)
        return;
    SelectObject(hdc, _curPen);

	float left = _center.x - radius;
	float top = _center.y - radius;
	float right = _center.x + radius;
	float bottom = _center.y + radius;
	Ellipse(hdc, left, top, right, bottom);
}

bool CircleCollider::IsCollision(const Vector2& pos)
{
    if (_isActive == false)
        return false;

    Vector2 centerToPos = pos - _center;
    float length = centerToPos.Length();

    return length <= radius;
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> circle)
{
    Vector2 centerToCenter = circle->_center - _center;
    float length = centerToCenter.Length();

    return length <= (radius + circle->radius);
}

bool CircleCollider::IsCollision(const shared_ptr<class RectCollider> rect)
{
    return rect->IsCollision(shared_from_this());
}
