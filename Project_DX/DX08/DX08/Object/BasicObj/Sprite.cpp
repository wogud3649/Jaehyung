#include "framework.h"
#include "Sprite.h"

Sprite::Sprite(wstring file, Vector2 size)
: _clipSize(size)
{
    _maxFrame = { 1,1 };

    Sprite::CreateMaterial(file);
    Sprite::CreateMesh();

    _transform = make_shared<Transform>();
    _actionBuffer = make_shared<ActionBuffer>();
    _actionBuffer->_data.imageSize = _srv->GetImageSize();

    _reverseBuffer = make_shared<ReverseBuffer>();
}

Sprite::Sprite(wstring file, Vector2 maxFrame, Vector2 size)
: _maxFrame(maxFrame)
, _clipSize(size)
{
    Sprite::CreateMaterial(file);
    Sprite::CreateMesh();

    _transform = make_shared<Transform>();
    _actionBuffer = make_shared<ActionBuffer>();

    _actionBuffer->_data.imageSize = _srv->GetImageSize();
    _actionBuffer->_data.size.x = _actionBuffer->_data.imageSize.x / _maxFrame.x;
    _actionBuffer->_data.size.y = _actionBuffer->_data.imageSize.y / _maxFrame.y;

    _reverseBuffer = make_shared<ReverseBuffer>();
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
    _actionBuffer->Update();
    _reverseBuffer->Update();
    Quad::Update();
}

void Sprite::Render()
{
    _actionBuffer->SetPSBuffer(0);
    _reverseBuffer->SetPSBuffer(1);
    Quad::Render();
}

void Sprite::CreateMesh()
{
    Vertex vertex;

    Vector2 halfSize = _clipSize * 0.5f;
    halfSize.x = halfSize.x / _maxFrame.x;
    halfSize.y = halfSize.y / _maxFrame.y;

    vertex.pos = { -halfSize.x, halfSize.y, 0.0f }; // 왼쪽 위
    vertex.uv = { 0.0f, 0.0f };
    _vertices.push_back(vertex);

    vertex.pos = { halfSize.x, halfSize.y, 0.0f }; // 오른쪽 위
    vertex.uv = { 1.0f, 0.0f };
    _vertices.push_back(vertex);

    vertex.pos = { -halfSize.x, -halfSize.y, 0.0f }; // 왼쪽 아래
    vertex.uv = { 0.0f, 1.0f };
    _vertices.push_back(vertex);

    vertex.pos = { halfSize.x, -halfSize.y, 0.0f }; // 오른쪽 아래
    vertex.uv = { 1.0f, 1.0f };
    _vertices.push_back(vertex);

    _indices.push_back(0); // 왼쪽 위
    _indices.push_back(1); // 오른쪽 위
    _indices.push_back(2); // 왼쪽 아래

    _indices.push_back(1); // 오른쪽 위
    _indices.push_back(3); // 오른쪽 아래
    _indices.push_back(2); // 왼쪽 아래

    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), 4);
    _indexBuffer = make_shared<IndexBuffer>(_indices.data(), 6);
}

void Sprite::CreateMaterial(wstring file)
{
	_vs = ADD_VS(L"Shader/TextureVertexShader.hlsl");
	_ps = ADD_PS(L"Shader/ActionPixelShader.hlsl");
	_srv = SRV_ADD(file);
    _size = _srv->GetImageSize();
}

void Sprite::SetReverse()
{
    if (_reverseBuffer->_data.reverse == 0)
        _reverseBuffer->_data.reverse = 1;
    else
        _reverseBuffer->_data.reverse = 0;
}

void Sprite::SetCurFrame(Vector2 curFrame)
{
    _actionBuffer->_data.startPos.x = _actionBuffer->_data.size.x / curFrame.x;
    _actionBuffer->_data.startPos.y = _actionBuffer->_data.size.y / curFrame.y;
}

void Sprite::SetActionClip(Action::Clip clip)
{
    _actionBuffer->_data.startPos = clip._startPos;
    _actionBuffer->_data.size = clip._size;
}
