#include "framework.h"
#include "SpriteSlider.h"

SpriteSlider::SpriteSlider()
{
}

SpriteSlider::SpriteSlider(wstring file, Vector2 maxFrame)
{
    _maxFrame = maxFrame;

    CreateMaterial(file);
    CreateMesh();

	_transform = make_shared<Transform>();

	_actionBuffer = make_shared<ActionBuffer>();
	_actionBuffer->_data.imageSize = _imageSize;
	_actionBuffer->_data.size = _size;

	_sliderBuffer = make_shared<SliderBuffer>();
	_sliderBuffer->_data.ratio = 0.0f;
    _sliderBuffer->_data.opaque = 0.8f;
}

SpriteSlider::~SpriteSlider()
{
}

void SpriteSlider::Update()
{
	_actionBuffer->Update();
	_sliderBuffer->Update();

    _transform->Update();
}

void SpriteSlider::PostRender()
{
    _actionBuffer->SetPSBuffer(0);
    _sliderBuffer->SetPSBuffer(1);

    _vertexBuffer->IASet(0);
    _indexBuffer->IASetIndexBuffer();

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    ALPHA->SetState();
    _srv->Set(0);
    SAMPLER->Set(0);

    _transform->SetBuffer(0);

    _vs->Set();
    _ps->Set();

    DC->DrawIndexed(6, 0, 0);
}

void SpriteSlider::CreateMesh()
{
    Vertex vertex;

    Vector2 halfSize = _imageSize * 0.5f;
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

void SpriteSlider::CreateMaterial(wstring file)
{
    _vs = ADD_VS(L"Shader/TextureVertexShader.hlsl");
    _ps = ADD_PS(L"Shader/UI/SliderSpritePixelShader.hlsl");
    _srv = SRV_ADD(file);
    _imageSize = _srv->GetImageSize();
    _size.x = _imageSize.x / _maxFrame.x;
    _size.y = _imageSize.y / _maxFrame.y;
}

void SpriteSlider::SetPos(Vector2 pos)
{
}

void SpriteSlider::SetCurFrame(Vector2 curFrame)
{
	_actionBuffer->_data.startPos.x = curFrame.x * _actionBuffer->_data.size.x;
	_actionBuffer->_data.startPos.y = curFrame.y * _actionBuffer->_data.size.y;
}