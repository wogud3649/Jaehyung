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

    return OBB_DESC();
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
