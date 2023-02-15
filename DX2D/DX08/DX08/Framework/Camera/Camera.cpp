#include "framework.h"
#include "Camera.h"

Camera* Camera::_instance = nullptr;
Camera::Camera()
{
	_transform = make_shared<Transform>();
	_projection = make_shared<MatrixBuffer>();
	_uiCameraBuffer = make_shared<MatrixBuffer>();

	SetViewPort();
	
	XMMATRIX projMatrix = XMMatrixOrthographicOffCenterLH(0, WIN_WIDTH, 0, WIN_HEIGHT, 0.0f, 1.0f);
	_projection->SetData(projMatrix);
	_projection->Update();
}

Camera::~Camera()
{
	_target = nullptr;
}

void Camera::Update()
{
	if (_target == nullptr)
		FreeMode();
	else
		FollowMode();

	Shake();

	_transform->Update();
	_moveVector.x = -_transform->GetPos().x;
	_moveVector.y = -_transform->GetPos().y;
}

void Camera::PostRender()
{
	ImGui::SliderFloat2("CameraPos", (float*)&_moveVector, -2000.0f, 2000.0f);
}

void Camera::ShakeStart(float magnitude, float duration, float reduceDamping)
{
	_magnitude = magnitude;
	_duration = duration;
	_reduceDamping = reduceDamping;
	_originPos = _transform->GetPos();
}

void Camera::SetViewPort(UINT width, UINT height)
{
	D3D11_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	DC->RSSetViewports(1, &vp);

	win_size.x = width;
	win_size.y = height;
}

void Camera::SetProjectionBuffer(UINT width, UINT height)
{
	_projection->SetVSBuffer(2);
}

void Camera::Shake()
{
	if (_duration <= 0.0f)
		return;

	_duration -= DELTA_TIME;
	_magnitude -= _reduceDamping * DELTA_TIME;
	
	if (_magnitude <= 0.0f)
	{
		_magnitude = 0.0f;
		_duration = 0.0f;
	}

	Vector2 randomPos;
	randomPos.x = _originPos.x + MathUtility::RandomFloat(-_magnitude, _magnitude);
	randomPos.y = _originPos.y + MathUtility::RandomFloat(-_magnitude, _magnitude);
	_transform->SetPosition(randomPos);

	if (_duration <= 0.0f)
	{
		_transform->SetPosition(_originPos);
	}
}

void Camera::FreeMode()
{
	if (KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS('W'))
			_transform->GetPos().y -= _speed * DELTA_TIME;
		if (KEY_PRESS('S'))
			_transform->GetPos().y += _speed * DELTA_TIME;
		if (KEY_PRESS('A'))
			_transform->GetPos().x += _speed * DELTA_TIME;
		if (KEY_PRESS('D'))
			_transform->GetPos().x -= _speed * DELTA_TIME;
	}
}

void Camera::FollowMode()
{
	Vector2 targetPos = _target->GetWorldPos() - _offset;
	
	if (targetPos.x < _leftBottom.x)
		targetPos.x = _leftBottom.x;

	if (targetPos.x > _rightTop.x - win_size.x)
		targetPos.x = _rightTop.x - win_size.x;

	if (targetPos.y < _leftBottom.y)
		targetPos.y = _leftBottom.y;

	if (targetPos.y > _rightTop.y - win_size.y)
		targetPos.y = _rightTop.y - win_size.y;

	Vector2 lerp = LERP(_transform->GetWorldPos(), -targetPos, DELTA_TIME * 5.0f);
	_transform->SetPosition(lerp);
}
