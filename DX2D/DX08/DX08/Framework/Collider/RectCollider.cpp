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

Vector2 RectCollider::GetWorldHalfSize()
{
    OBB_DESC info = GetOBB();

    Vector2 result;
    result.x = (info.direction[0]* info.length[0]).Length();
    result.y = (info.direction[1]* info.length[1]).Length();

    return result;
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

HIT_RESULT RectCollider::Block(shared_ptr<CircleCollider> other)
{
    HIT_RESULT result;

    if (IsAABB(other))
    {
        Vector2 circlePos = other->GetTransform()->GetWorldPos();
        Vector2 rectPos = _transform->GetWorldPos();
        Vector2 leftTop = Vector2(Left(), Top());
        Vector2 rightTop = Vector2(Right(), Top());
        Vector2 leftBottom = Vector2(Left(), Bottom());
        Vector2 rightBottom = Vector2(Right(), Bottom());

        Vector2 halfSize = GetWorldHalfSize();

        if (circlePos.x > leftTop.x && circlePos.x < rightTop.x)
        {
            Vector2 dir = Vector2(0.0f, circlePos.y - rectPos.y);
            dir.Normalize();

            float sum = other->WorldRadius() + halfSize.y;
            float distance = abs(rectPos.y - circlePos.y);

            other->GetTransform()->GetPos() += dir * (sum - distance);
        }
        else if (circlePos.y > leftBottom.y && circlePos.y < rightTop.y)
        {
            Vector2 dir = Vector2(circlePos.x - rectPos.x, 0.0f);
            dir.Normalize();

            float sum = other->WorldRadius() + halfSize.x;
            float distance = abs(rectPos.x - circlePos.x);

            other->GetTransform()->GetPos() += dir * (sum - distance);
        }
        else
        {
            Vector2 closerVertex = GetCloserVertex(other);

            Vector2 vToCircle = circlePos - closerVertex;

            Vector2 dir = circlePos - closerVertex;
            float magnitude = other->WorldRadius() - dir.Length();
            dir.Normalize();
            other->GetTransform()->GetPos() += dir * magnitude;
        }

        result.isHit = true;

        return result;
    }
    result.isHit = false;
    return result;
}

HIT_RESULT RectCollider::Block(shared_ptr<RectCollider> other)
{
    HIT_RESULT result;
    if (IsAABB(other))
    {
        Vector2 dir = other->GetTransform()->GetWorldPos() - _transform->GetWorldPos();
        Vector2 sum = Vector2(GetWorldHalfSize().x + other->GetWorldHalfSize().x, GetWorldHalfSize().y + other->GetWorldHalfSize().y);
        Vector2 overlap = Vector2(sum.x - abs(dir.x), sum.y - abs(dir.y));

        if (overlap.x >= overlap.y)
        {
            other->GetTransform()->GetPos().y += dir.NormalVector2().y * overlap.y;
        }
        else
        {
            other->GetTransform()->GetPos().x += dir.NormalVector2().x * overlap.x;
        }

        result.isHit = true;
    }

    result.isHit = false;
    return result;
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

Vector2 RectCollider::GetCloserVertex(shared_ptr<CircleCollider> circle)
{
    Vector2 circlePos = circle->GetTransform()->GetWorldPos();
    Vector2 leftTop = Vector2(Left(), Top());
    Vector2 rightTop = Vector2(Right(), Top());
    Vector2 leftBottom = Vector2(Left(), Bottom());
    Vector2 rightBottom = Vector2(Right(), Bottom());

    int leftTopL = (int)(leftTop - circlePos).Length();
    int rightTopL = (int)(rightTop - circlePos).Length();
    int leftBottomL = (int)(leftBottom - circlePos).Length();
    int rightBottomL = (int)(rightBottom - circlePos).Length();

    int min;
    min = min(leftTopL, min(rightTopL, min(leftBottomL, rightBottomL)));

    if (leftTopL == min)
        return leftTop;
    else if (rightTopL == min)
        return rightTop;
    else if (leftBottomL == min)
        return leftBottom;
    else
        return rightBottom;
}

Vector2 RectCollider::GetCloserVertex(shared_ptr<RectCollider> rect)
{
    return Vector2();
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
