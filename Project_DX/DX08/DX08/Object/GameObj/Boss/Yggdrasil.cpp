#include "framework.h"
#include "Yggdrasil.h"

Yggdrasil::Yggdrasil()
{
	_body = make_shared<Quad>(L"Resources/Texture/Boss/Yggdrasil/Body.png", Vector2(2, 1));
}

Yggdrasil::~Yggdrasil()
{
}

void Yggdrasil::Update()
{
	_body->Update();
}

void Yggdrasil::Render()
{
	_body->Render();
}
