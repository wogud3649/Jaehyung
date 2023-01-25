#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2 size)
: _size(size)
{
    CreateData();
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
    _transform->Update();
    _colorBuffer->Update();
}

void RectCollider::Render()
{
    _transform->SetBuffer(0);
    _colorBuffer->SetPSBuffer(0);
    
    _vertexBuffer->IASet(0);

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

    _vs->Set();
    _ps->Set();

    DC->Draw(_vertices.size(), 0);
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> other)
{
    Vector2 CenterToCenter = this->GetOBB().position - other->GetOBB().position;

    Vector2 standards[4] = {
        this->GetOBB().direction[0],
        this->GetOBB().direction[1],
        other->GetOBB().direction[0],
        other->GetOBB().direction[1]
    };

    float lengths[4] = {
        this->GetOBB().length[0],
        this->GetOBB().length[1],
        other->GetOBB().length[0],
        other->GetOBB().length[1]
    };

    float temp1, temp2;

    //case1
    temp1 = abs(CenterToCenter.Dot(standards[0]));
    temp2 = SeparateAxis(standards[0], standards[2] * lengths[2], standards[3] * lengths[3]) + lengths[0];
    if (temp1 > temp2)
        return false;

    //case2
    temp1 = abs(CenterToCenter.Dot(standards[1]));
    temp2 = SeparateAxis(standards[1], standards[2] * lengths[2], standards[3] * lengths[3]) + lengths[1];
    if (temp1 > temp2)
        return false;

    //case3
    temp1 = abs(CenterToCenter.Dot(standards[2]));
    temp2 = SeparateAxis(standards[2], standards[0] * lengths[0], standards[1] * lengths[1]) + lengths[2];
    if (temp1 > temp2)
        return false;

    //case4
    temp1 = abs(CenterToCenter.Dot(standards[3]));
    temp2 = SeparateAxis(standards[3], standards[0] * lengths[0], standards[1] * lengths[1]) + lengths[3];
    if (temp1 > temp2)
        return false;

    return true;
}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> circle)
{
    Vector2 CenterToCenter = this->GetOBB().position - circle->GetTransform()->GetWorldPos();

    Vector2 standards[3] = {
        this->GetOBB().direction[0],
        this->GetOBB().direction[1],
        CenterToCenter.NormalVector2()
    };

    float lengths[2] = {
        this->GetOBB().length[0],
        this->GetOBB().length[1],
    };

    float temp1, temp2;

    temp1 = abs(CenterToCenter.Dot(standards[0]));
    temp2 = circle->GetRadius() * circle->GetTransform()->GetWorldScale().x + lengths[0];
    if (temp1 > temp2)
        return false;

    temp1 = abs(CenterToCenter.Dot(standards[1]));
    temp2 = circle->GetRadius() * circle->GetTransform()->GetWorldScale().x + lengths[1];
    if (temp1 > temp2)
        return false;

    temp1 = CenterToCenter.Length();
    temp2 = circle->GetRadius() * circle->GetTransform()->GetWorldScale().x + SeparateAxis(standards[2], standards[0] * lengths[0], standards[1] * lengths[1]);
    if (temp1 > temp2)
        return false;

    return true;
}

RectCollider::OBB_DESC RectCollider::GetOBB()
{
    OBB_DESC desc;
    desc.position = _transform->GetWorldPos();

    XMFLOAT4X4 matrix;
    XMStoreFloat4x4(&matrix, _transform->GetMatrix());

    desc.direction[0] = { matrix._11,matrix._12 };
    desc.direction[1] = { matrix._21,matrix._22 };
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

void RectCollider::CreateVertices()
{
    Vertex_Basic vertex;

    Vector2 halfSize = _size * 0.5f;

    vertex = { -halfSize.x, halfSize.y, 0.0f }; // 왼쪽 위
    _vertices.push_back(vertex);

    vertex = { halfSize.x, halfSize.y, 0.0f }; // 오른쪽 위
    _vertices.push_back(vertex);

    vertex = { halfSize.x, -halfSize.y, 0.0f }; // 오른쪽 아래
    _vertices.push_back(vertex);

    vertex = { -halfSize.x, -halfSize.y, 0.0f }; // 왼쪽 아래
    _vertices.push_back(vertex);

    vertex = { -halfSize.x, halfSize.y, 0.0f }; // 왼쪽 위
    _vertices.push_back(vertex);
}
