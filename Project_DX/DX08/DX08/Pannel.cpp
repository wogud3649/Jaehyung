#include "framework.h"
#include "Pannel.h"

Pannel::Pannel()
{
	_quad = make_shared<Quad>();
}

Pannel::~Pannel()
{
}

void Pannel::Update()
{
	_quad->Update();
}

void Pannel::Render()
{
	_quad->Render();
}
