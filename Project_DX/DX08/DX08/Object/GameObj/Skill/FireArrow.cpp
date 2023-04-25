#include "framework.h"
#include "FireArrow.h"

FireArrow::FireArrow()
{
	Skill::Skill();

	_quad = make_shared<Quad>(L"Resources/Texture/Effect/Wizard/FireArrow/FireArrow.png");
	_quad->GetTransform()->SetParent(_transform);
	_quad->SetPS(ADD_PS(L"Shader/LRTexturePixelShader.hlsl"));
	_col = make_shared<CircleCollider>(12);

	_col->GetTransform()->SetParent(_quad->GetTransform());
	_col->DeActivate();

	_reverseBuffer = make_shared<ReverseBuffer>();

	_isActive = false;
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
		DeActivate();
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

void FireArrow::SetActive()
{
	_quad->Update();
	_col->GetTransform()->Update();

	_isActive = true;

	_col->Activate();
}

void FireArrow::SetRight(bool isRight)
{
	_isRight = isRight;
	_reverseBuffer->_data.reverse = !_isRight;
}

void FireArrow::Hit()
{
	DeActivate();
}

void FireArrow::DeActivate()
{
	_isActive = false;

	_curDuration = _maxDuration;
	_quad->GetTransform()->SetPos(Vector2(0, 0));

	_col->DeActivate();
}