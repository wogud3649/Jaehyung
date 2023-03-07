#include "framework.h"
#include "Slot.h"

Slot::Slot()
{
	_quad = make_shared<Quad>(Vector2(70, 70));
	_quad->SetPS(ADD_PS(L"Shader/UI/SlotPixelShader.hlsl"));
}

Slot::~Slot()
{
}

void Slot::Update()
{
	_quad->Update();
}

void Slot::Render()
{
	_quad->Render();
}
