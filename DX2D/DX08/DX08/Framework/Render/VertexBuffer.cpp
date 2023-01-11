#include "framework.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
    CreateVertices();
    CreateVertexBuffer();
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::CreateVertices()
{
    Vertex vertex;

    vertex.pos = { -0.5f, 0.5f, 0.0f }; // 왼쪽 위
    vertex.uv = { 0.0f, 0.0f };
    vertices.push_back(vertex);

    vertex.pos = { 0.5f, -0.5f, 0.0f }; // 오른쪽 아래
    vertex.uv = { -1.0f, 1.0f };
    vertices.push_back(vertex);

    vertex.pos = { -0.5f, -0.5f, 0.0f }; // 왼쪽 아래
    vertex.uv = { 0.0f, 1.0f };
    vertices.push_back(vertex);

    vertex.pos = { -0.5f, 0.5f, 0.0f }; // 왼쪽 위
    vertex.uv = { 0.0f, 0.0f };
    vertices.push_back(vertex);

    vertex.pos = { 0.5f, 0.5f, 0.0f }; // 오른쪽 위
    vertex.uv = { -1.0f, 0.0f };
    vertices.push_back(vertex);

    vertex.pos = { 0.5f, -0.5f, 0.0f }; // 오른쪽 아래
    vertex.uv = { -1.0f, 1.0f };
    vertices.push_back(vertex);

    stride = sizeof(Vertex);
    offset = 0;
}

void VertexBuffer::CreateVertexBuffer()
{
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = stride * vertices.size();
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertices.data();

    DEVICE->CreateBuffer(&bd, &initData, vertexBuffer.GetAddressOf());
}

void VertexBuffer::Set(int slot)
{
    DC->IASetVertexBuffers(slot, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
}
