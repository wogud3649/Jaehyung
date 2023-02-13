#include "framework.h"
#include "FilterSprite.h"

FilterSprite::FilterSprite(wstring file, Vector2 size)
: _clipSize(size)
{
    _maxFrame = { 1,1 };

    CreateMaterial(file);
    CreateMesh();

    _transform = make_shared<Transform>();
    _actionBuffer = make_shared<ActionBuffer>();
    _actionBuffer->_data.imageSize = _srv->GetImageSize();

    _reverseBuffer = make_shared<ReverseBuffer>();

    _filterBuffer = make_shared<FilterBuffer>();
    _filterBuffer->_data.value1 = 500;
}

FilterSprite::FilterSprite(wstring file, Vector2 maxFrame, Vector2 size)
: _maxFrame(maxFrame)
, _clipSize(size)
{
    CreateMaterial(file);
    CreateMesh();

    _transform = make_shared<Transform>();
    _actionBuffer = make_shared<ActionBuffer>();

    _actionBuffer->_data.imageSize = _srv->GetImageSize();
    _actionBuffer->_data.size.x = _actionBuffer->_data.imageSize.x / _maxFrame.x;
    _actionBuffer->_data.size.y = _actionBuffer->_data.imageSize.y / _maxFrame.y;

    _reverseBuffer = make_shared<ReverseBuffer>();

    _filterBuffer = make_shared<FilterBuffer>();
}

FilterSprite::~FilterSprite()
{
}

void FilterSprite::Update()
{
    _actionBuffer->Update();
    _reverseBuffer->Update();
    _filterBuffer->Update();
    Quad::Update();
}

void FilterSprite::Render()
{
    _actionBuffer->SetPSBuffer(0);
    _reverseBuffer->SetPSBuffer(1);
    _filterBuffer->SetPSBuffer(2);
    Quad::Render();
}

void FilterSprite::CreateMesh()
{
    Vertex vertex;

    Vector2 halfSize = _clipSize * 0.5f;
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

void FilterSprite::CreateMaterial(wstring file)
{
    _vs = ADD_VS(L"Shader/TextureVertexShader.hlsl");
    _ps = ADD_PS(L"Shader/ActionFilterPixelShader.hlsl");
    _srv = SRV_ADD(file);
    _size = _srv->GetImageSize();
}

void FilterSprite::SetReverse()
{
    if (_reverseBuffer->_data.reverse == 0)
        _reverseBuffer->_data.reverse = 1;
    else
        _reverseBuffer->_data.reverse = 0;
}

void FilterSprite::SetCurFrame(Vector2 curFrame)
{
    _actionBuffer->_data.startPos.x = _actionBuffer->_data.size.x / curFrame.x;
    _actionBuffer->_data.startPos.y = _actionBuffer->_data.size.y / curFrame.y;
}

void FilterSprite::SetActionClip(Action::Clip clip)
{
    _actionBuffer->_data.startPos = clip._startPos;
    _actionBuffer->_data.size = clip._size;
}
