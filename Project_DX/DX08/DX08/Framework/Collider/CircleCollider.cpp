#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius)
    : _radius(radius)
{
    _type = Collider::Type::CIRCLE;
    CreateData();
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
    Collider::Update();
}

void CircleCollider::Render()
{
    Collider::Render();
}

void CircleCollider::CreateData()
{
    CreateVertices();

    _vs = make_shared<VertexShader>(L"Shader/Collider/ColliderVertexShader.hlsl");
    _ps = make_shared<PixelShader>(L"Shader/Collider/ColliderPixelShader.hlsl");

    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex_Basic), _vertices.size());

    _colorBuffer = make_shared<ColorBuffer>();
    _colorBuffer->_data.color = { 0,1,0,1 };
    _transform = make_shared<Transform>();
}

HIT_RESULT CircleCollider::IsCollision(Vector2 pos)
{
    HIT_RESULT result;

    Vector2 dir = pos - _transform->GetWorldPos();
    float length = dir.Length();
    float worldRadius = WorldRadius();

    result.distance = dir;

    result.isHit = length <= worldRadius;

    if (result.isHit)
    {
        if (dir.x < 0 && dir.y >= 0)
            result.dir = Direction::LEFTUP;
        else if (dir.x < 0 && dir.y < 0)
            result.dir = Direction::LEFTDOWN;
        else if (dir.x >= 0 && dir.y >= 0)
            result.dir = Direction::RIGHTUP;
        else
            result.dir = Direction::RIGHTDOWN;
    }

    return result;
}

HIT_RESULT CircleCollider::IsCollision(shared_ptr<CircleCollider> other, bool isObb)
{
    HIT_RESULT result;

    float radiusSum = WorldRadius() * _transform->GetWorldScale().x + other->WorldRadius() * other->GetTransform()->GetWorldScale().x;

    Vector2 otherPos = other->GetTransform()->GetWorldPos();
    Vector2 thisPos = _transform->GetWorldPos();
    Vector2 centerToCenter = otherPos - thisPos;

    result.distance = centerToCenter;

    if (otherPos.x < thisPos.x && otherPos.y >= thisPos.y)
        result.dir = Direction::LEFTUP;
    else if (otherPos.x < thisPos.x && otherPos.y < thisPos.y)
        result.dir = Direction::LEFTDOWN;
    else if (otherPos.x >= thisPos.x && otherPos.y >= thisPos.y)
        result.dir = Direction::RIGHTUP;
    else if (otherPos.x >= thisPos.x && otherPos.y < thisPos.y)
        result.dir = Direction::RIGHTDOWN;

    result.isHit = (centerToCenter).Length() < radiusSum;
    return result;
}

HIT_RESULT CircleCollider::IsCollision(shared_ptr<RectCollider> other, bool isObb)
{
    HIT_RESULT result;

    Vector2 circlePos = _transform->GetWorldPos();
    Vector2 rectPos = other->GetTransform()->GetWorldPos();

    Vector2 centerToCenter = rectPos - circlePos;
    result.distance = centerToCenter;

    float left = other->Left();
    float right = other->Right();
    float top = other->Top();
    float bottom = other->Bottom();

    if (circlePos.x < right && circlePos.x > left && circlePos.y < top && circlePos.y > bottom)
    {
        result.isHit = true;

        Vector2 closerVertex = GetCloserVertex(other);
        Vector2 dir = circlePos - closerVertex;

        if (abs(dir.x) >= abs(dir.y))
        {
            if (dir.y >= 0)
            {
                result.dir = Direction::UP;
                dir.y += WorldRadius();
                dir.x = 0;
            }
            else
            {
                result.dir = Direction::DOWN;
                dir.y -= WorldRadius();
                dir.x = 0;
            }
        }
        else
        {
            if (dir.x >= 0)
            {
                result.dir = Direction::RIGHT;
                dir.x += WorldRadius();
                dir.y = 0;
            }
            else
            {
                result.dir = Direction::LEFT;
                dir.x -= WorldRadius();
                dir.y = 0;
            }
        }

        return result;
    }
    else if (circlePos.x < right && circlePos.x > left)
    {
        float dir = rectPos.y - circlePos.y;

        if (circlePos.y < top + WorldRadius() && circlePos.y > bottom - WorldRadius())
        {
            result.isHit = true;

            if (dir >= 0)
                result.dir = Direction::UP;
            else
                result.dir = Direction::DOWN;

            return result;
        }
    }
    else if (circlePos.y < top && circlePos.y > bottom)
    {
        float dir = rectPos.x - circlePos.x;

        if (circlePos.x < right + WorldRadius() && circlePos.x > left - WorldRadius())
        {
            result.isHit = true;

            if (dir >= 0)
                result.dir = Direction::RIGHT;
            else
                result.dir = Direction::LEFT;

            return result;
        }
    }

    Vector2 leftTop = Vector2(left, top);
    Vector2 leftBottom = Vector2(left, bottom);
    Vector2 rightTop = Vector2(right, top);
    Vector2 rightBottom = Vector2(right, bottom);

    result = other->IsCollision(leftTop);
    if (result.isHit)
    {
        result.distance = centerToCenter;
        result.dir = Direction::RIGHTDOWN;
        return result;
    }

    result = other->IsCollision(leftBottom);
    if (result.isHit)
    {
        result.distance = centerToCenter;
        result.dir = Direction::RIGHTUP;
        return result;
    }

    result = other->IsCollision(rightTop);
    if (result.isHit)
    {
        result.distance = centerToCenter;
        result.dir = Direction::LEFTDOWN;
        return result;
    }

    result = other->IsCollision(rightBottom);
    if (result.isHit)
    {
        result.distance = centerToCenter;
        result.dir = Direction::LEFTUP;
        return result;
    }

    result.distance = { 0,0 };
    return result;
}

HIT_RESULT CircleCollider::Block(shared_ptr<CircleCollider> other)
{
    HIT_RESULT result = IsCollision(other);

    if (result.isHit)
    {
        float radiusSum = other->WorldRadius() + WorldRadius();
        float overlap = radiusSum - result.distance.Length();
        other->GetTransform()->Move(result.distance.NormalVector2() * overlap);
    }

    return result;
}

HIT_RESULT CircleCollider::Block(shared_ptr<RectCollider> other)
{
    HIT_RESULT result  = IsCollision(other);

    if (result.isHit)
    {
        Vector2 halfSize = other->GetWorldHalfSize();

        if (result.dir == Direction::UP || result.dir == Direction::DOWN)
        {
            float dir = result.distance.y;
            float distance = abs(dir);

            if (dir >= 0)
                dir = 1;
            else
                dir = -1;

            float sum = WorldRadius() + halfSize.y;

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

            float sum = WorldRadius() + halfSize.x;

            other->GetTransform()->MoveX(dir * (sum - distance));
        }
        else
        {
            Vector2 circlePos = _transform->GetWorldPos();
            Vector2 closerVertex = GetCloserVertex(other);
            Vector2 dir = closerVertex - circlePos;

            float magnitude = WorldRadius() - dir.Length();
            dir.Normalize();
            other->GetTransform()->Move(dir * magnitude);
        }
    }

    return result;
}

float CircleCollider::WorldRadius()
{
    return _radius * _transform->GetWorldScale().x;
}

Vector2 CircleCollider::GetCloserVertex(shared_ptr<RectCollider> rect)
{
    Vector2 circlePos = _transform->GetWorldPos();
    Vector2 leftTop = Vector2(rect->Left(), rect->Top());
    Vector2 rightTop = Vector2(rect->Right(), rect->Top());
    Vector2 leftBottom = Vector2(rect->Left(), rect->Bottom());
    Vector2 rightBottom = Vector2(rect->Right(), rect->Bottom());

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

void CircleCollider::CreateVertices()
{
    float angle = PI / 6.0f;

    for (int i = 0; i < 13; i++)
    {
        Vertex_Basic vertex;
        vertex.pos = XMFLOAT3(cos(angle * i) * _radius, sin(angle * i) * _radius, 0);
        _vertices.push_back(vertex);
    }
}