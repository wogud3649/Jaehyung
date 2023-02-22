#include "framework.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(void* data, UINT stride, UINT count, UINT offset, bool instance)
: _data(data)
, _stride(stride)
, _count(count)
, _offset(offset)
, _instance(instance)
{
    if (_instance)
        CreateVertexBuffer_Instance();
    else
        CreateVertexBuffer();
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::CreateVertexBuffer()
{
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = _stride * _count;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = _data;

    DEVICE->CreateBuffer(&bd, &initData, _buffer.GetAddressOf());
}

void VertexBuffer::CreateVertexBuffer_Instance()
{
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.ByteWidth = _stride * _count;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bd.MiscFlags = 0;
    bd.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = _data;
    initData.SysMemPitch = 0;
    initData.SysMemSlicePitch = 0;

    DEVICE->CreateBuffer(&bd, &initData, _buffer.GetAddressOf());
}

void VertexBuffer::IASet(int slot)
{
    DC->IASetVertexBuffers(slot, 1, _buffer.GetAddressOf(), &_stride, &_offset);
}

void VertexBuffer::Update()
{
    if (_instance == false)
        return;

    DC->Map(_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &_subResource);
    memcpy(_subResource.pData, _data, (size_t)(_count * _stride));
    DC->Unmap(_buffer.Get(), 0);
}
