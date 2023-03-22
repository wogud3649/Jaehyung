#include "framework.h"
#include "Collider.h"

bool Collider::_isDebug = false;

Collider::Collider()
{
}

Collider::~Collider()
{
}

void Collider::Update()
{
    if (!_isActive)
        return;

    _transform->Update();
    _colorBuffer->Update();
}

void Collider::Render()
{
    if (!_isDebug || !_isActive)
        return;

    _transform->SetBuffer(0);
    _colorBuffer->SetPSBuffer(0);

    _vertexBuffer->IASet(0);

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

    _vs->Set();
    _ps->Set();

    DC->Draw(_vertices.size(), 0);
}

HIT_RESULT Collider::IsCollision(shared_ptr<Collider> other, bool isObb)
{
    HIT_RESULT result;

    switch (other->_type)
    {
    case Collider::NONE:
        result.isHit = false;
        return result;
        break;
    case Collider::CIRCLE:
        return IsCollision(dynamic_pointer_cast<CircleCollider>(other), isObb);
        break;
    case Collider::RECT:
        return IsCollision(dynamic_pointer_cast<RectCollider>(other), isObb);
        break;
    default:
        break;
    }

    result.isHit = false;
    return result;
}
