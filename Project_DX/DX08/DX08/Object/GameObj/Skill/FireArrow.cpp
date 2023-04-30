#include "framework.h"
#include "FireArrow.h"

FireArrow::FireArrow()
{
	_power = 50.0f;

	_quad = make_shared<Quad>(L"Resources/Texture/Effect/Wizard/FireArrow/FireArrow.png");
	_quad->GetTransform()->SetParent(_transform);
	_quad->SetPS(ADD_PS(L"Shader/LRTexturePixelShader.hlsl"));
	_col = make_shared<CircleCollider>(12);

	_col->GetTransform()->SetParent(_quad->GetTransform());
	_col->DeActivate();
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
	Skill::Render();

	if (_isActive == false)
		return;

	_quad->Render();
	_col->Render();
}

void FireArrow::SetActive()
{
	Skill::SetActive();

	_quad->Update();
	_col->GetTransform()->Update();

	_col->Activate();
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