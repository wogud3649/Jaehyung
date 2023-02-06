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
    if (this->IsCollision(other))
    {
        Vector2 dir = other->GetTransform()->GetWorldPos() - _transform->GetWorldPos();
        Vector2 sum = Vector2(other->GetWorldSize().x / 2 + WorldRadius(), other->GetWorldSize().y / 2 + WorldRadius());
        Vector2 overlap = Vector2(sum.x - abs(dir.x),sum.y - abs(dir.y));

        if (other->Right() >= _transform->GetWorldPos().x && other->Left() <= _transform->GetWorldPos().x)
        {
            if (_transform->GetWorldPos().y < other->GetTransform()->GetWorldPos().y)
            {
                other->GetTransform()->GetPos().y += overlap.y;
            }
            else
            {
                other->GetTransform()->GetPos().y -= overlap.y;
            }
        }
        else if (other->Top() >= _transform->GetWorldPos().y && other->Bottom() <= _transform->GetWorldPos().y)
        {
            if (_transform->GetWorldPos().x < other->GetTransform()->GetWorldPos().x)
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
            Vector2 diagonal = Vector2(other->GetWorldSize().x / 2, other->GetWorldSize().y / 2);
            float diagonalSum = diagonal.Length() + WorldRadius();
            float diagonalOverlap = diagonalSum - dir.Length();
            other->GetTransform()->GetPos() += Vector2(dir.NormalVector2().x * diagonalOverlap, dir.NormalVector2().y * diagonalOverlap);
        }

        return true;
    }

    return false;
}

float CircleCollider::WorldRadius()
{
    return _radius * _transform->GetScale().x;
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