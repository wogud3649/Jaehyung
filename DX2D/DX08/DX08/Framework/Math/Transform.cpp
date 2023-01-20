#include "framework.h"
#include "Transform.h"

Transform::Transform()
{
	_world = make_shared<MatrixBuffer>();
}

Transform::~Transform()
{
}

void Transform::Update()
{
	// SRT Matrix ¼³Á¤
	_scaleM = XMMatrixScaling(_scale.x, _scale.y, 1);
	_rotationM = XMMatrixRotationZ(_angle);
	_translateM = XMMatrixTranslation(_pos.x, _pos.y, 0);

	_srtMatrix = _scaleM * _rotationM * _translateM;

	if (_parent.expired() == false)
	{
		_srtMatrix *= _parent.lock()->GetMatrix();
	}

	_world->SetData(_srtMatrix);
	_world->Update();
}

void Transform::SetBuffer(UINT slot)
{
	_world->SetVSBuffer(0);
}

Vector2 Transform::GetWorldPos()
{
	XMFLOAT4X4 temp;
	XMStoreFloat4x4(&temp, _srtMatrix);

	return Vector2(temp._41, temp._42);
}

Vector2 Transform::GetWorldScale()
{
	XMFLOAT4X4 temp;
	XMStoreFloat4x4(&temp, _srtMatrix);

	return Vector2(temp._11, temp._22);
}
