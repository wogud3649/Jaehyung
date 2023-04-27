#include "framework.h"
#include "ThrowHead.h"

ThrowHead::ThrowHead()
{
	_quad = make_shared<Quad>(L"Resources/Texture/SKUL/Head.png");
	_quad->GetTransform()->SetParent(_transform);
	_quad->SetPS(ADD_PS(L"Shader/LRTexturePixelShader.hlsl"));
	_quad->GetTransform()->SetScale(Vector2(2, 2));
	_col = make_shared<CircleCollider>(12);

	_col->GetTransform()->SetParent(_quad->GetTransform());
	_col->DeActivate();
}

ThrowHead::~ThrowHead()
{
}

void ThrowHead::Update()
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

void ThrowHead::Render()
{
	Skill::Render();

	if (_isActive == false)
		return;

	_quad->Render();
	_col->Render();
}

void ThrowHead::SetActive()
{
	Skill::SetActive();

	_quad->Update();
	_col->GetTransform()->Update();

	_col->Activate();
}

void ThrowHead::Hit()
{
	DeActivate();
}

void ThrowHead::DeActivate()
{
	_isActive = false;

	_curDuration = _maxDuration;
	_quad->GetTransform()->SetPos(Vector2(0, 0));

	_col->DeActivate();

	_endEvent();
}
