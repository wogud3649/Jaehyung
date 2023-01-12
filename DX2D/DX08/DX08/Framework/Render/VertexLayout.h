#pragma once
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
