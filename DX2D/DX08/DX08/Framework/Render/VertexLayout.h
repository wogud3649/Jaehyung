#pragma once

struct Vertex_Basic
{
    Vertex_Basic() {}
    Vertex_Basic(float x, float y, float z)
        : pos(x, y, z)
    {

    }

    XMFLOAT3 pos;
};
struct Vertex
{
    Vertex() {}
    Vertex(float x, float y, float z)
        : pos(x, y, z)
    {

    }

    XMFLOAT3 pos;
    XMFLOAT2 uv;
};
