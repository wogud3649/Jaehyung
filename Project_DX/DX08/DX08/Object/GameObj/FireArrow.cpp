#include "framework.h"
#include "FireArrow.h"

FireArrow::FireArrow()
{
	_quad = make_shared<Quad>(L"Resources/Texture/Effect/Wizard/FireArrow/FireArrow.png");
	_quad->SetPS(ADD_PS(L"Shader/LRTexturePixelShader.hlsl"));
	_col = make_shared<CircleCollider>(12);

	_col->GetTransform()->SetParent(_quad->GetTransform());

	_reverseBuffer = make_shared<ReverseBuffer>();
}

FireArrow::~FireArrow()
{
}

void FireArrow::Update()
{
	if (_isActive == false)
		return;

	_col->Update();
	_quad->Update();
	_reverseBuffer->Update();

	if (_isRight)
		_quad->GetTransform()->MoveX(_speed * DELTA_TIME);
	else
		_quad->GetTransform()->MoveX(-_speed * DELTA_TIME);

	_curDuration -= DELTA_TIME;

	if (_curDuration < 0)
	{
		_curDuration = _maxDuration;
		_isActive = false;
	}
}

void FireArrow::Render()
{
	if (_isActive == false)
		return;

	_reverseBuffer->SetPSBuffer(2);
	_quad->Render();
	_col->Render();
}

void FireArrow::SetRight(bool isRight)
{
	_isRight = isRight;
	_reverseBuffer->_data.reverse = !_isRight;
}

void FireArrow::Hit()
{
	_col->DeActivate();
}