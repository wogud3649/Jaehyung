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

HIT_RESULT RectCollider::IsCollision(Vector2 pos)
{
    HIT_RESULT result;

    float left = Left();
    float right = Right();
    float top = Top();
    float bottom = Bottom();

    Vector2 dir = pos - this->GetTransform()->GetWorldPos();
    result.distance = dir;

    if (pos.x <= right && pos.x >= left && pos.y <= top && pos.y >= bottom)
    {
        result.isHit = true;

        if (dir.x < 0 && dir.y >= 0)
        {
            result.dir = Direction::LEFTUP;
        }
        else if (dir.x < 0 && dir.y < 0)
        {
            result.dir = Direction::LEFTDOWN;
        }
        if (dir.x >= 0 && dir.y >= 0)
        {
            result.dir = Direction::RIGHTUP;
        }
        else if (dir.x >= 0 && dir.y < 0)
        {
            result.dir = Direction::RIGHTDOWN;
        }

        return result;
    }

    result.isHit = false;
    result.dir = Direction::NONE;
    return result;
}

HIT_RESULT RectCollider::IsCollision(shared_ptr<CircleCollider> other, bool isObb)
{
    if (isObb)
        return IsOBB(other);
    else
        return IsAABB(other);
}

HIT_RESULT RectCollider::IsCollision(shared_ptr<RectCollider> other, bool isObb)
{
    if (isObb)
        return IsOBB(other);
    else
        return IsAABB(other);
}

HIT_RESULT RectCollider::SideCollision(shared_ptr<CircleCollider> other)
{
    HIT_RESULT result;

    Vector2 circlePos = other->GetTransform()->GetWorldPos();

    float left = Left();
    float right = Right();
    float top = Top();
    float bottom = Bottom();
    Vector2 dir = circlePos - this->GetTransform()->GetWorldPos();

    if (circlePos.y <= top + other->WorldRadius() && circlePos.y >= bottom - other->WorldRadius())
    {
        if (circlePos.x <= right + other->WorldRadius() && circlePos.x >= left - other->WorldRadius())
        {
            result.isHit = true;

            if (dir.x >= 0)
                result.dir = Direction::RIGHT;
            else
                result.dir = Direction::LEFT;

            result.distance = dir;
        }
    }

    return result;
}

HIT_RESULT RectCollider::Block(shared_ptr<CircleCollider> other)
{
    HIT_RESULT result = IsAABB(other);

    if (result.isHit)
    {
        Vector2 halfSize = GetWorldHalfSize();

        if (result.dir == Direction::UP || result.dir == Direction::DOWN)
        {
            float dir = result.distance.y;
            float distance = abs(dir);
            
            if (dir >= 0)
                dir = 1;
            else
                dir = -1;

            float sum = other->WorldRadius() + halfSize.y;

            other->GetTransform()->MoveY(dir * (sum - distance));
        }
        else if (result.dir == Direction::LEFT || result.dir == Direction::RIGHT)
        {
            float dir = result.distance.x;
            float distance = abs(dir);

            if (dir >= 0)
                dir = 1;
            else
                dir = -1;

            float sum = other->WorldRadius() + halfSize.x;

            other->GetTransform()->MoveX(dir * (sum - distance));
        }
        else
        {
            Vector2 closerVertex = other->GetCloserVertex(shared_from_this());
            Vector2 dir = other->GetTransform()->GetWorldPos() - closerVertex;

            float magnitude = other->WorldRadius() - dir.Length();
            dir.Normalize();
            other->GetTransform()->Move(dir * magnitude);
        }
    }

    return result;
}

HIT_RESULT RectCollider::Block(shared_ptr<RectCollider> other)
{
    HIT_RESULT result = IsAABB(other);

    if (result.isHit)
    {
        Vector2 sum = Vector2(GetWorldHalfSize().x + other->GetWorldHalfSize().x, GetWorldHalfSize().y + other->GetWorldHalfSize().y);
        Vector2 overlap = Vector2(sum.x - abs(result.distance.x), sum.y - abs(result.distance.y));

        if (overlap.x >= overlap.y)
        {
            other->GetTransform()->MoveY(result.distance.NormalVector2().y * overlap.y);
        }
        else
        {
            other->GetTransform()->MoveX(result.distance.NormalVector2().x * overlap.x);
        }
    }

    return result;
}

HIT_RESULT RectCollider::TopBlock(shared_ptr<CircleCollider> other)
{
    HIT_RESULT result = IsAABB(other);
    if (result.isHit)
    {
        if (other->GetTransform()->GetPos().x < Left() || other->GetTransform()->GetPos().x > Right())
        {
            result.isHit = false;
            return result;
        }

        float dir = other->GetTransform()->GetWorldPos().y - Top();
        if (dir < 0.0f)
        {
            result.isHit = false;
            result.dir = Direction::NONE;
            return result;
        }

        float sum = other->WorldRadius();
        float overlap = sum - dir;

        other->GetTransform()->MoveY(overlap);
        result.dir = Direction::UP;
    }

    return result;
}

HIT_RESULT RectCollider::IsAABB(shared_ptr<RectCollider> other)
{
    HIT_RESULT result;

    Vector2 leftTop = Vector2(other->Left(), other->Top());
    Vector2 leftBottom = Vector2(other->Left(), other->Bottom());
    Vector2 rightTop = Vector2(other->Right(), other->Top());
    Vector2 rightBottom = Vector2(other->Right(), other->Bottom());

    Vector2 dir = other->GetTransform()->GetWorldPos() - _transform->GetWorldPos();

    result.distance = dir;
    
    result = IsCollision(leftTop);
    if (result.isHit)
        return result;

    result = IsCollision(leftBottom);
    if (result.isHit)
        return result;

    result = IsCollision(rightTop);
    if (result.isHit)
        return result;

    result = IsCollision(rightBottom);
    if (result.isHit)
        return result;

    leftTop = Vector2(Left(), Top());
    leftBottom = Vector2(Left(), Bottom());
    rightTop = Vector2(Right(), Top());
    rightBottom = Vector2(Right(), Bottom());

    result = other->IsCollision(leftTop);
    if (result.isHit)
    {
        result.dir = Direction::LEFTUP;
        return result;
    }

    result = other->IsCollision(leftBottom);
    if (result.isHit)
    {
        result.dir = Direction::LEFTDOWN;
        return result;
    }

    result = other->IsCollision(rightTop);
    if (result.isHit)
    {
        result.dir = Direction::RIGHTUP;
        return result;
    }

    result = other->IsCollision(rightBottom);
    if (result.isHit)
    {
        result.dir = Direction::RIGHTDOWN;
        return result;
    }

    result.dir = Direction::NONE;
    return result;
}

HIT_RESULT RectCollider::IsAABB(shared_ptr<CircleCollider> other)
{
    HIT_RESULT result;
    
    Vector2 circlePos = other->GetTransform()->GetWorldPos();

    float left = Left();
    float right = Right();
    float top = Top();
    float bottom = Bottom();

    Vector2 centerToCenter = circlePos - _transform->GetWorldPos();
    result.distance = centerToCenter;

    if (circlePos.x < right && circlePos.x > left && circlePos.y < top && circlePos.y > bottom)
    {
        result.isHit = true;

        Vector2 closerVertex = other->GetCloserVertex(shared_from_this());
        Vector2 dir = closerVertex - circlePos;

        if (abs(dir.x) >= abs(dir.y))
        {
            if (dir.y >= 0)
            {
                result.dir = Direction::UP;
                dir.y += other->WorldRadius();
                dir.x = 0;
            }
            else
            {
                result.dir = Direction::DOWN;
                dir.y -= other->WorldRadius();
                dir.x = 0;
            }
        }
        else
        {
            if (dir.x >= 0)
            {
                result.dir = Direction::RIGHT;
                dir.x += other->WorldRadius();
                dir.y = 0;
            }
            else
            {
                result.dir = Direction::LEFT;
                dir.x -= other->WorldRadius();
                dir.y = 0;
            }
        }

        return result;
    }
    else if (circlePos.x < right && circlePos.x > left)
    {
        if (circlePos.y < top + other->WorldRadius() && circlePos.y > bottom - other->WorldRadius())
        {
            result.isHit = true;

            if (centerToCenter.y >= 0)
                result.dir = Direction::UP;
            else
                result.dir = Direction::DOWN;

            return result;
        }
    }
    else if (circlePos.y < top && circlePos.y > bottom)
    {
        if (circlePos.x < right + other->WorldRadius() && circlePos.x > left - other->WorldRadius())
        {
            result.isHit = true;

            if (centerToCenter.x >= 0)
                result.dir = Direction::RIGHT;
            else
                result.dir = Direction::LEFT;

            return result;
        }
    }

    Vector2 leftTop = Vector2(Left(), Top());
    Vector2 leftBottom = Vector2(Left(), Bottom());
    Vector2 rightTop = Vector2(Right(), Top());
    Vector2 rightBottom = Vector2(Right(), Bottom());

    result = other->IsCollision(leftTop);
    if (result.isHit)
    {
        result.distance = centerToCenter;
        result.dir = Direction::LEFTUP;
        return result;
    }

    result = other->IsCollision(leftBottom);
    if (result.isHit)
    {
        result.distance = centerToCenter;
        result.dir = Direction::LEFTDOWN;
        return result;
    }

    result = other->IsCollision(rightTop);
    if (result.isHit)
    {
        result.distance = centerToCenter;
        result.dir = Direction::RIGHTUP;
        return result;
    }

    result = other->IsCollision(rightBottom);
    if (result.isHit)
    {
        result.distance = centerToCenter;
        result.dir = Direction::RIGHTDOWN;
        return result;
    }

    result.dir = Direction::NONE;
    return result;
}

HIT_RESULT RectCollider::IsOBB(shared_ptr<RectCollider> other)
{
    HIT_RESULT result;

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
    {
        result.isHit = false;
        return result;
    }

    // nea2 기준으로 투영
    lengthA = ea2.Length();
    lengthB = SeparateAxis(nea2, eb1, eb2);
    length = abs(nea2.Dot(aToB));
    if (length > lengthA + lengthB)
    {
        result.isHit = false;
        return result;
    }

    // neb1 기준으로 투영
    lengthB = eb1.Length();
    lengthA = SeparateAxis(neb1, ea1, ea2);
    length = abs(neb1.Dot(aToB));
    if (length > lengthA + lengthB)
    {
        result.isHit = false;
        return result;
    }

    // neb2 기준으로 투영
    lengthB = eb2.Length();
    lengthA = SeparateAxis(neb2, ea1, ea2);
    length = abs(neb2.Dot(aToB));
    if (length > lengthA + lengthB)
    {
        result.isHit = false;
        return result;
    }

    result.isHit = true;
    return result;
}

HIT_RESULT RectCollider::IsOBB(shared_ptr<CircleCollider> other)
{
    HIT_RESULT result;

    OBB_DESC aInfo = GetOBB();

    Vector2 aToB = aInfo.position - other->GetTransform()->GetWorldPos();

    Vector2 nea1 = aInfo.direction[0];
    Vector2 ea1 = nea1 * aInfo.length[0];
    Vector2 nea2 = aInfo.direction[1];
    Vector2 ea2 = nea2 * aInfo.length[1];

    float d = sqrtf(powf(aInfo.length[0], 2) + powf(aInfo.length[1], 2)) + other->WorldRadius();

    if (aToB.Length() > d)
    {
        result.isHit = false;
        return result;
    }

    // nea1 기준으로 투영
    float lengthA = ea1.Length();
    float lengthB = other->WorldRadius();
    float length = abs(nea1.Dot(aToB));
    if (length > lengthA + lengthB)
    {
        result.isHit = false;
        return result;
    }

    // nea2 기준으로 투영
    lengthA = ea2.Length();
    lengthB = other->WorldRadius();
    length = abs(nea2.Dot(aToB));
    if (length > lengthA + lengthB)
    {
        result.isHit = false;
        return result;
    }

    result.isHit = true;
    return result;
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
