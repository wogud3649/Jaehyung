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

bool CircleCollider::IsCollision(Vector2 pos)
{
    float length = (pos - _transform->GetWorldPos()).Length();
    float worldRadius = WorldRadius();

    return length < worldRadius;
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> other, bool isObb)
{
    float radiusSum = this->_radius * this->GetTransform()->GetWorldScale().x + other->_radius * other->GetTransform()->GetWorldScale().x;
    float distance = (other->_transform->GetWorldPos() - this->_transform->GetWorldPos()).Length();

    return distance < radiusSum;
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> other, bool isObb)
{
    return other->IsCollision(shared_from_this(), isObb);
}

bool CircleCollider::Block(shared_ptr<CircleCollider> other)
{
    if (this->IsCollision(other))
    {
        Vector2 dir = other->GetTransform()->GetWorldPos() - _transform->GetWorldPos();
        float radiusSum = other->WorldRadius() + WorldRadius();
        float overlap = radiusSum - dir.Length();;
        other->GetTransform()->GetPos() += dir.NormalVector2() * overlap;

        return true;
    }

    return false;
}

bool CircleCollider::Block(shared_ptr<RectCollider> other)
{
    //HIT_RESULT result;

    if (other->IsAABB(shared_from_this()))
    {
        Vector2 circlePos = _transform->GetWorldPos();
        Vector2 rectPos = other->GetTransform()->GetWorldPos();
        Vector2 leftTop = Vector2(other->Left(), other->Top());
        Vector2 rightTop = Vector2(other->Right(), other->Top());
        Vector2 leftBottom = Vector2(other->Left(), other->Bottom());
        Vector2 rightBottom = Vector2(other->Right(), other->Bottom());

        Vector2 halfSize = other->GetWorldHalfSize();

        if (circlePos.x > leftTop.x && circlePos.x < rightTop.x)
        {
            Vector2 dir = Vector2(0.0f, rectPos.y - circlePos.y);
            dir.Normalize();

            float sum = WorldRadius() + halfSize.y;
            float distance = abs(rectPos.y - circlePos.y);

            other->GetTransform()->GetPos() += dir * (sum - distance);
            
            //result.isHit = true;
        }
        else if (circlePos.y > leftBottom.y && circlePos.y < rightTop.y)
        {
            Vector2 dir = Vector2(rectPos.x - circlePos.x, 0.0f);
            dir.Normalize();

            float sum = WorldRadius() + halfSize.x;
            float distance = abs(rectPos.x - circlePos.x);

            other->GetTransform()->GetPos() += dir * (sum - distance);

            //result.isHit = true;
        }
        else
        {
            Vector2 closerVertex = GetCloserVertex(other);

            Vector2 vToCircle = circlePos - closerVertex;

            Vector2 dir = closerVertex - circlePos;
            float magnitude = WorldRadius() - dir.Length();
            dir.Normalize();
            other->GetTransform()->GetPos() += dir * magnitude;

            //result.isHit = true;
        }

        return true;
    }

    return false;
}

float CircleCollider::WorldRadius()
{
    return _radius * _transform->GetScale().x;
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
    float angle = PI / 18.0f;

    for (int i = 0; i < 37; i++)
    {
        Vertex_Basic vertex;
        vertex.pos = XMFLOAT3(cos(angle * i) * _radius, sin(angle * i) * _radius, 0);
        _vertices.push_back(vertex);
    }
}