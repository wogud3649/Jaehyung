#include "framework.h"
#include "Quad.h"

Quad::Quad()
{
}

Quad::Quad(wstring file)
{
    CreateMaterial(file);
    CreateMesh();

    _transform = make_shared<Transform>();
}

Quad::~Quad()
{
}

void Quad::Update()
{
    _transform->Update();
}

void Quad::Render()
{
    _vertexBuffer->IASet(0);
    _indexBuffer->IASetIndexBuffer();

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    //ALPHA->SetState();
    _srv->Set(0);
    SAMPLER->Set(0);

    _transform->SetBuffer(0);

    _vs->Set();
    _ps->Set();

    DC->DrawIndexed(6, 0, 0);
}

void Quad::SetRender()
{
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    //ALPHA->SetState();
    _srv->Set(0);
    SAMPLER->Set(0);

    _transform->SetBuffer(0);

    _vs->Set();
    _ps->Set();
}

void Quad::CreateMaterial(wstring file)
{
    _vs = ADD_VS(L"Shader/TextureVertexShader.hlsl");
	_ps = ADD_PS(L"Shader/TexturePixelShader.hlsl");
    _srv = SRV_ADD(file);
    _size = _srv->GetImageSize();
}

void Quad::CreateMesh()
{
    Vertex vertex;

    Vector2 halfSize = _size * 0.5f;

    vertex.pos = { -halfSize.x, halfSize.y, 0.0f }; // ���� ��
    vertex.uv = { 0.0f, 0.0f };
    _vertices.push_back(vertex);

    vertex.pos = { halfSize.x, halfSize.y, 0.0f }; // ������ ��
    vertex.uv = { 1.0f, 0.0f };
    _vertices.push_back(vertex);

    vertex.pos = { -halfSize.x, -halfSize.y, 0.0f }; // ���� �Ʒ�
    vertex.uv = { 0.0f, 1.0f };
    _vertices.push_back(vertex);

    vertex.pos = { halfSize.x, -halfSize.y, 0.0f }; // ������ �Ʒ�
    vertex.uv = { 1.0f, 1.0f };
    _vertices.push_back(vertex);

    _indices.push_back(0); // ���� ��
    _indices.push_back(1); // ������ ��
    _indices.push_back(2); // ���� �Ʒ�

    _indices.push_back(1); // ������ ��
    _indices.push_back(3); // ������ �Ʒ�
    _indices.push_back(2); // ���� �Ʒ�

    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), 4);
    _indexBuffer = make_shared<IndexBuffer>(_indices.data(), 6);
}