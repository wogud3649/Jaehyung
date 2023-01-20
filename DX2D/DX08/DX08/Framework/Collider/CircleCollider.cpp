#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius)
: _radius(radius)
{
	CreateData();
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
	_transform->Update();
	_colorBuffer->Update();
}

void CircleCollider::Render()
{
	_transform->SetBuffer(0);
	_colorBuffer->SetPSBuffer(0);

	_vertexBuffer->IASet(0);

	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	_vs->Set();
	_ps->Set();

	DC->Draw(_vertices.size(), 0);
}

void CircleCollider::CreateData()
{
	CreateVertices();

	_vs = make_shared<VertexShader>(L"Shader/Collider/ColliderVertexShader.hlsl");
	_ps = make_shared<PixelShader>(L"Shader/Collider/ColliderPixelShader.hlsl");

	_vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex_Basic), _vertices.size());

	_colorBuffer = make_shared<ColorBuffer>();
	_colorBuffer->_data.color = { 0,1,0,1 };
	_transform = make_shared<Transform>();
}

void CircleCollider::CreateVertices()
{
	Vertex_Basic vertex;
	float theta;

	for (int i = 0; i < 361; i++)
	{
		theta = i * PI / 180;
		vertex = { _radius * cos(theta), _radius * sin(theta), 0.0f };
		_vertices.push_back(vertex);
	}
}
