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

HIT_RESULT RectCollider::SideCollision(shared_ptr<CircleCollider> other)
{
    HIT_RESULT result;
    if (IsAABB(other))
    {
        Vector2 circlePos = other->GetTransform()->GetWorldPos();
        Vector2 rectPos = _transform->GetWorldPos();

        Vector2 dir = Vector2(circlePos.x - rectPos.x, 0.0f);
        dir.Normalize();

        if (dir.x > 0)
            result.dir = Direction::RIGHT;
        else
            result.dir = Direction::LEFT;
    }
    else
    {
        result.isHit = false;
    }
    return result;
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

        if (circlePos.x > leftTop.x && circlePos.x < rightTop.x && circlePos.y > leftBottom.y && circlePos.y < rightTop.y)
        {
            Vector2 closerVertex = other->GetCloserVertex(shared_from_this());

            Vector2 dir = closerVertex - circlePos;

            if (abs(dir.x) >= abs(dir.y) && dir.y >= 0)
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

            other->GetTransform()->Move(dir);
        }
        else if (circlePos.x > leftTop.x && circlePos.x < rightTop.x)
        {
            Vector2 dir = Vector2(0.0f, circlePos.y - rectPos.y);
            dir.Normalize();

            if (dir.y > 0)
                result.dir = Direction::UP;
            else
                result.dir = Direction::DOWN;

            float sum = other->WorldRadius() + halfSize.y;
            float distance = abs(rectPos.y - circlePos.y);

            other->GetTransform()->Move(dir * (sum - distance));
        }
        else if (circlePos.y > leftBottom.y && circlePos.y < rightTop.y)
        {
            Vector2 dir = Vector2(circlePos.x - rectPos.x, 0.0f);
            dir.Normalize();

            if (dir.x > 0)
                result.dir = Direction::RIGHT;
            else
                result.dir = Direction::LEFT;

            float sum = other->WorldRadius() + halfSize.x;
            float distance = abs(rectPos.x - circlePos.x);

            other->GetTransform()->Move(dir * (sum - distance));
        }
        else
        {
            Vector2 closerVertex = other->GetCloserVertex(shared_from_this());

            Vector2 dir = circlePos - closerVertex;

            if (dir.x < 0 && dir.y > 0)
                result.dir == Direction::LEFTUP;
            else if (dir.x > 0 && dir.y > 0)
                result.dir == Direction::RIGHTUP;
            else if (dir.x < 0 && dir.y < 0)
                result.dir == Direction::LEFTDOWN;
            else
                result.dir == Direction::RIGHTDOWN;

            float magnitude = other->WorldRadius() - dir.Length();
            dir.Normalize();
            other->GetTransform()->Move(dir * magnitude);
        }
        result.isHit = true;
    }
    else
    {
        result.isHit = false;
    }
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
            other->GetTransform()->MoveY(dir.NormalVector2().y * overlap.y);
        }
        else
        {
            other->GetTransform()->MoveX(dir.NormalVector2().x * overlap.x);
        }
        result.isHit = true;
    }
    else
    {
        result.isHit = false;
    }
    return result;
}

HIT_RESULT RectCollider::TopBlock(shared_ptr<CircleCollider> other)
{
    HIT_RESULT result;
    if (IsAABB(other))
    {
        if (other->GetTransform()->GetPos().x < Left() || other->GetTransform()->GetPos().x > Right())
            return result;
        float dir = abs(other->GetTransform()->GetWorldPos().y - Top());
        float sum = other->WorldRadius();
        float overlap = sum - dir;

        if (overlap > 0.0f)
        {
            other->GetTransform()->MoveY(overlap);
            result.dir = Direction::UP;
            result.isHit = true;

            return result;
        }
    }
    else
    {
        result.isHit = false;
    }
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

    // n : Normal ����
    // e : edge ����

    Vector2 nea1 = aInfo.direction[0];
    Vector2 ea1 = nea1 * aInfo.length[0];
    Vector2 nea2 = aInfo.direction[1];
    Vector2 ea2 = nea2 * aInfo.length[1];

    Vector2 neb1 = bInfo.direction[0];
    Vector2 eb1 = neb1 * bInfo.length[0];
    Vector2 neb2 = bInfo.direction[1];
    Vector2 eb2 = neb2 * bInfo.length[1];

    // nea1 �������� ����
    float lengthA = ea1.Length();
    float lengthB = SeparateAxis(nea1, eb1, eb2);
    float length = abs(nea1.Dot(aToB));
    if (length > lengthA + lengthB)
        return false;

    // nea2 �������� ����
    lengthA = ea2.Length();
    lengthB = SeparateAxis(nea2, eb1, eb2);
    length = abs(nea2.Dot(aToB));
    if (length > lengthA + lengthB)
        return false;

    // neb1 �������� ����
    lengthB = eb1.Length();
    lengthA = SeparateAxis(neb1, ea1, ea2);
    length = abs(neb1.Dot(aToB));
    if (length > lengthA + lengthB)
        return false;

    // neb2 �������� ����
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

    // nea1 �������� ����
    float lengthA = ea1.Length();
    float lengthB = other->WorldRadius();
    float length = abs(nea1.Dot(aToB));
    if (length > lengthA + lengthB)
        return false;

    // nea2 �������� ����
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

    vertex.pos = { -halfSize.x, halfSize.y, 0.0f }; // ���� ��
    _vertices.push_back(vertex);

    vertex.pos = { halfSize.x, halfSize.y, 0.0f }; // ������ ��
    _vertices.push_back(vertex);

    vertex.pos = { halfSize.x, -halfSize.y, 0.0f }; // ������ �Ʒ�
    _vertices.push_back(vertex);

    vertex.pos = { -halfSize.x, -halfSize.y, 0.0f }; // ���� �Ʒ�
    _vertices.push_back(vertex);

    vertex.pos = { -halfSize.x, halfSize.y, 0.0f }; // ���� ��
    _vertices.push_back(vertex);
}
