#include "framework.h"
#include "Quad.h"

Quad::Quad(wstring file)
{
    CreateMaterial(file);
    CreateMesh();

    _world = make_shared<MatrixBuffer>();
}

Quad::~Quad()
{
}

void Quad::Update()
{
    _world->Update();
}

void Quad::Render()
{
    _vertexBuffer->Set(0);
    _indexBuffer->IASetIndexBuffer();

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    _srv->Set(0);
    _sampler->Set(0);

    _world->SetVSBuffer(0);

    _vs->Set();
    _ps->Set();

    DC->DrawIndexed(6, 0, 0);
}

void Quad::CreateMaterial(wstring file)
{
	_vs = make_shared<VertexShader>(L"Shader/TutorialShader.hlsl");
	_ps = make_shared<PixelShader>(L"Shader/TutorialShader.hlsl");
	_srv = make_shared<SRV>(file);
    _size = _srv->GetImageSize();

	_sampler = make_shared<SamplerState>();
}

void Quad::CreateMesh()
{
    Vertex vertex;

    Vector2 halfSize = _size * 0.3f;

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