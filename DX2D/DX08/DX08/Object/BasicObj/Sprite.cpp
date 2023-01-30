#include "framework.h"
#include "Sprite.h"

Sprite::Sprite(wstring file, Vector2 maxFrame)
: _maxFrame(maxFrame)
{
    Sprite::CreateMaterial(file);
    Sprite::CreateMesh();

    _transform = make_shared<Transform>();
    _spriteBuffer = make_shared<SpriteBuffer>();
    _spriteBuffer->_data.maxFrame = maxFrame;

    _reverseBuffer = make_shared<ReverseBuffer>();
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
    _spriteBuffer->Update();
    _reverseBuffer->Update();
    Quad::Update();
}

void Sprite::Render()
{
    _spriteBuffer->SetPSBuffer(0);
    _reverseBuffer->SetPSBuffer(1);
    Quad::Render();
}

void Sprite::CreateMesh()
{
    Vertex vertex;

    Vector2 halfSize = _size * 0.5f;
    halfSize.x = halfSize.x / _maxFrame.x;
    halfSize.y = halfSize.y / _maxFrame.y;

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

void Sprite::CreateMaterial(wstring file)
{
	_vs = ADD_VS(L"Shader/TextureVertexShader.hlsl");
	_ps = ADD_PS(L"Shader/SpritePixelShader.hlsl");
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

void Sprite::SetActionClip(Action::Clip clip)
{
    Vector2 imageSize = clip._srv->GetImageSize();

    _spriteBuffer->_data.curFrame = { clip._startPos.x / clip._size.x, clip._startPos.y / clip._size.y };
}
