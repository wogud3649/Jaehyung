#include "framework.h"
#include "ArkBlock.h"

ArkBlock::ArkBlock()
{
	_rect = make_shared<RectCollider>(Vector2(0, 0), _size);
}

ArkBlock::~ArkBlock()
{
}

void ArkBlock::Update()
{
	_rect->Update();
}

void ArkBlock::Render(HDC hdc)
{
	_rect->Render(hdc);
}
