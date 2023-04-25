#include "framework.h"
#include "Potion.h"

Potion::Potion()
{
	_quad = make_shared<Quad>(L"Resources/Texture/Potion/M.png");
	_col = make_shared<CircleCollider>(11);
	_col->GetTransform()->SetParent(_quad->GetTransform());
	DeActivate();
}

Potion::~Potion()
{
}

void Potion::Update()
{
	if (_isActive == false)
		return;

	_quad->Update();
	_col->Update();

	if (_col->GetActive())
	{
		if (PLAYER->GetBodyCollider()->GetActive())
		{
			HIT_RESULT result = _col->IsCollision(PLAYER->GetBodyCollider());
			if (result.isHit)
			{
				PLAYER->Heal(_healValue);
				DeActivate();
			}
		}
	}
}

void Potion::Render()
{
	if (_isActive == false)
		return;

	_quad->Render();
	_col->Render();
}

void Potion::Activate()
{
	_isActive = true;
	_col->Activate();
}

void Potion::DeActivate()
{
	_isActive = false;
	_col->DeActivate();
}
