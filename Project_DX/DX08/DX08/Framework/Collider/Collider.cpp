#include "framework.h"
#include "Collider.h"

bool Collider::isDebug = false;

Collider::Collider()
{
}

Collider::~Collider()
{
}

void Collider::Update()
{
    if (!isActive)
        return;

    _transform->Update();
    _colorBuffer->Update();
}

void Collider::Render()
{
    if (!isDebug || !isActive)
        return;

    _transform->SetBuffer(0);
    _colorBuffer->SetPSBuffer(0);

    _vertexBuffer->IASet(0);

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

    _vs->Set();
    _ps->Set();

    DC->Draw(_vertices.size(), 0);
}

bool Collider::IsCollision(shared_ptr<Collider> other, bool isObb)
{
    switch (other->_type)
    {
    case Collider::NONE:
        return false;
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

    return false;
}
