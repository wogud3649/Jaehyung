#include "framework.h"
#include "Slot.h"

Slot::Slot()
{
	_col = make_shared<RectCollider>(Vector2(53, 53));
}

Slot::~Slot()
{
}

void Slot::Update()
{
	_col->Update();

	HIT_RESULT result = _col->IsCollision(MOUSE_POS);
	if (result.isHit)
		_col->SetRed();
	else
		_col->SetGreen();
}

void Slot::Render()
{
	_col->Render();
}
