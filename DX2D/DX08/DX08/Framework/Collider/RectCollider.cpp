#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2 size)
    : _size(size)
{
    _type = Collider::Type::RECT;
    CreateData();
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
    Collider::Update();
}

void RectCollider::Render()
{
    Collider::Render();
}

RectCollider::OBB_DESC RectCollider::GetOBB()
{
    OBB_DESC desc;
    desc.position = _transform->GetWorldPos();

    XMFLOAT4X4 matrix;
    XMStoreFloat4x4(&matrix, _transform->GetMatrix());

    desc.direction[0] = { matrix._11, matrix._12 };
    desc.direction[1] = { matrix._21, matrix._22 };
    desc.direction[0].Normalize();
    desc.direction[1].Normalize();

    Vector2 halfSize = _size * 0.5f;

    desc.length[0] = halfSize.x * _transform->GetWorldScale().x;
    desc.length[1] = halfSize.y * _transform->GetWorldScale().y;

    return desc;
}

float RectCollider::SeparateAxis(Vector2 separate, Vector2 e1, Vector2 e2)
{
    float r1 = abs(separate.Dot(e1));
    float r2 = abs(separate.Dot(e2));

    return r1 + r2;
}

Vector2 RectCollider::GetWorldSize()
{
    return Vector2(_size.x * _transform->GetScale().x, _size.y * _transform->GetScale().y);
}

void RectCollider::CreateData()
{
    CreateVertices();

    _vs = make_shared<VertexShader>(L"Shader/Collider/ColliderVertexShader.hlsl");
    _ps = make_shared<PixelShader>(L"Shader/Collider/ColliderPixelShader.hlsl");

    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex_Basic), _vertices.size());

    _colorBuffer = make_shared<ColorBuffer>();
    _colorBuffer->_data.color = { 0,1,0,1 };
    _transform = make_shared<Transform>();
}

bool RectCollider::IsCollision(Vector2 pos)
{
    float left = Left();
    float right = Right();
    float top = Top();
    float bottom = Bottom();

    if (pos.x < right && pos.x > left)
    {
        if (pos.y < top && pos.y > bottom)
            return true;
    }

    return false;
}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other, bool isObb)
{
    if (isObb)
        return IsOBB(other);
    else
        return IsAABB(other);
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> other, bool isObb)
{
    if (isObb)
        return IsOBB(other);
    else
        return IsAABB(other);
}

bool RectCollider::Block(shared_ptr<CircleCollider> other)
{
    if (this->IsCollision(other))
    {
        Vector2 dir = other->GetTransform()->GetWorldPos() - _transform->GetWorldPos();
        Vector2 sum = Vector2(GetWorldSize().x / 2 + other->WorldRadius(), GetWorldSize().y / 2 + other->WorldRadius());
        Vector2 overlap = Vector2(sum.x - abs(dir.x), sum.y - abs(dir.y));

        if (Right() >= other->GetTransform()->GetWorldPos().x && Left() <= other->GetTransform()->GetWorldPos().x)
        {
            if (other->GetTransform()->GetWorldPos().y > _transform->GetWorldPos().y)
            {
                other->GetTransform()->GetPos().y += overlap.y;
            }
            else
            {
                other->GetTransform()->GetPos().y -= overlap.y;
            }
        }
        else if (Top() >= other->GetTransform()->GetWorldPos().y && Bottom() <= other->GetTransform()->GetWorldPos().y)
        {
            if (other->GetTransform()->GetWorldPos().x > _transform->GetWorldPos().x)
            {
                other->GetTransform()->GetPos().x += overlap.x;
            }
            else
            {
                other->GetTransform()->GetPos().x -= overlap.x;
            }
        }
        else
        {
            Vector2 diagonal = Vector2(GetWorldSize().x / 2, GetWorldSize().y / 2);
            float diagonalSum = diagonal.Length() + other->WorldRadius();
            float diagonalOverlap = diagonalSum - dir.Length();
            other->GetTransform()->GetPos() += Vector2(dir.NormalVector2().x * diagonalOverlap, dir.NormalVector2().y * diagonalOverlap);
        }

        return true;
    }

    return false;
}

bool RectCollider::Block(shared_ptr<RectCollider> other)
{
    if (this->IsCollision(other))
    {
        Vector2 dir = other->GetTransform()->GetWorldPos() - GetTransform()->GetWorldPos();
        Vector2 sum = Vector2(GetWorldSize().x / 2 + other->GetWorldSize().x / 2, GetWorldSize().y / 2 + other->GetWorldSize().y / 2);
        Vector2 overlap = Vector2(sum.x - abs(dir.x), sum.y - abs(dir.y));

        if (overlap.x >= overlap.y)
        {
            other->GetTransform()->GetPos().y += dir.NormalVector2().y * overlap.y;
        }
        else
        {
            other->GetTransform()->GetPos().x += dir.NormalVector2().x * overlap.x;
        }
        
    }

    return false;
}

bool RectCollider::IsAABB(shared_ptr<RectCollider> other)
{
    Vector2 leftTop = Vector2(other->Left(), other->Top());
    Vector2 leftBottom = Vector2(other->Left(), other->Bottom());
    Vector2 rightTop = Vector2(other->Right(), other->Top());
    Vector2 rightBottom = Vector2(other->Right(), other->Bottom());

    if (IsCollision(leftTop) || IsCollision(leftBottom)
        || IsCollision(rightTop) || IsCollision(rightBottom))
        return true;

    leftTop = Vector2(Left(), Top());
    leftBottom = Vector2(Left(), Bottom());
    rightTop = Vector2(Right(), Top());
    rightBottom = Vector2(Right(), Bottom());

    if (other->IsCollision(leftTop) || other->IsCollision(leftBottom)
        || other->IsCollision(rightTop) || other->IsCollision(rightBottom))
        return true;

    return false;
}

bool RectCollider::IsAABB(shared_ptr<CircleCollider> other)
{
    Vector2 circlePos = other->GetTransform()->GetWorldPos();

    Vector2 leftTop = Vector2(Left(), Top());
    Vector2 leftBottom = Vector2(Left(), Bottom());
    Vector2 rightTop = Vector2(Right(), Top());
    Vector2 rightBottom = Vector2(Right(), Bottom());

    if (other->IsCollision(leftTop) || other->IsCollision(leftBottom)
        || other->IsCollision(rightTop) || other->IsCollision(rightBottom))
        return true;

    float left = Left();
    float right = Right();
    float top = Top();
    float bottom = Bottom();

    if (circlePos.x < right && circlePos.x > left)
    {
        if (circlePos.y < top + other->WorldRadius() && circlePos.y > bottom - other->WorldRadius())
            return true;
    }

    if (circlePos.y < top && circlePos.y > bottom)
    {
        if (circlePos.x < right + other->WorldRadius() && circlePos.x > left - other->WorldRadius())
            return true;
    }

    return false;
}

bool RectCollider::IsOBB(shared_ptr<RectCollider> other)
{
    OBB_DESC aInfo = GetOBB();
    OBB_DESC bInfo = other->GetOBB();

    Vector2 aToB = aInfo.position - bInfo.position;

    // n : Normal 약자
    // e : edge 약자

    Vector2 nea1 = aInfo.direction[0];
    Vector2 ea1 = nea1 * aInfo.length[0];
    Vector2 nea2 = aInfo.direction[1];
    Vector2 ea2 = nea2 * aInfo.length[1];

    Vector2 neb1 = bInfo.direction[0];
    Vector2 eb1 = neb1 * bInfo.length[0];
    Vector2 neb2 = bInfo.direction[1];
    Vector2 eb2 = neb2 * bInfo.length[1];

    // nea1 기준으로 투영
    float lengthA = ea1.Length();
    float lengthB = SeparateAxis(nea1, eb1, eb2);
    float length = abs(nea1.Dot(aToB));
    if (length > lengthA + lengthB)
        return false;

    // nea2 기준으로 투영
    lengthA = ea2.Length();
    lengthB = SeparateAxis(nea2, eb1, eb2);
    length = abs(nea2.Dot(aToB));
    if (length > lengthA + lengthB)
        return false;

    // neb1 기준으로 투영
    lengthB = eb1.Length();
    lengthA = SeparateAxis(neb1, ea1, ea2);
    length = abs(neb1.Dot(aToB));
    if (length > lengthA + lengthB)
        return false;

    // neb2 기준으로 투영
    lengthB = eb2.Length();
    lengthA = SeparateAxis(neb2, ea1, ea2);
    length = abs(neb2.Dot(aToB));
    if (length > lengthA + lengthB)
        return false;

    return true;
}

bool RectCollider::IsOBB(shared_ptr<CircleCollider> other)
{
    OBB_DESC aInfo = GetOBB();

    Vector2 aToB = aInfo.position - other->GetTransform()->GetWorldPos();

    Vector2 nea1 = aInfo.direction[0];
    Vector2 ea1 = nea1 * aInfo.length[0];
    Vector2 nea2 = aInfo.direction[1];
    Vector2 ea2 = nea2 * aInfo.length[1];

    float d = sqrtf(powf(aInfo.length[0], 2) + powf(aInfo.length[1], 2)) + other->WorldRadius();

    if (aToB.Length() > d)
        return false;

    // nea1 기준으로 투영
    float lengthA = ea1.Length();
    float lengthB = other->WorldRadius();
    float length = abs(nea1.Dot(aToB));
    if (length > lengthA + lengthB)
        return false;

    // nea2 기준으로 투영
    lengthA = ea2.Length();
    lengthB = other->WorldRadius();
    length = abs(nea2.Dot(aToB));
    if (length > lengthA + lengthB)
        return false;

    return true;
}

void RectCollider::CreateVertices()
{
    Vertex_Basic vertex;

    Vector2 halfSize = _size * 0.5f;

    vertex.pos = { -halfSize.x, halfSize.y, 0.0f }; // 왼쪽 위
    _vertices.push_back(vertex);

    vertex.pos = { halfSize.x, halfSize.y, 0.0f }; // 오른쪽 위
    _vertices.push_back(vertex);

    vertex.pos = { halfSize.x, -halfSize.y, 0.0f }; // 오른쪽 아래
    _vertices.push_back(vertex);

    vertex.pos = { -halfSize.x, -halfSize.y, 0.0f }; // 왼쪽 아래
    _vertices.push_back(vertex);

    vertex.pos = { -halfSize.x, halfSize.y, 0.0f }; // 왼쪽 위
    _vertices.push_back(vertex);
}
