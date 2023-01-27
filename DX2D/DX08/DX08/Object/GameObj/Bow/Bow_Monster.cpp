#include "framework.h"
#include "Bow_Monster.h"

Bow_Monster::Bow_Monster()
{
	_quad = make_shared<Quad>(L"Resource/Texture/Monster.png");
	_quad->GetTransform()->GetScale() *= 0.5;
	_quad->GetTransform()->GetPos() = { WIN_WIDTH - 300, WIN_HEIGHT - 200 };

	_col = make_shared<CircleCollider>(150);
	_col->GetTransform()->SetParent(_quad->GetTransform());
	_col->GetTransform()->GetPos().x += 40;
	_col->GetTransform()->GetPos().y -= 20;

	_hpImage = make_shared<Quad>(L"Resource/Texture/Dungreed/AED01.png");
	_hpImage->GetTransform()->SetParent(_col->GetTransform());
	_hpImage->GetTransform()->GetScale() *= 7;
	_hpImage->GetTransform()->GetPos().y += 300;
}

Bow_Monster::~Bow_Monster()
{
}

void Bow_Monster::Update()
{
	if (!isActive)
		return;

	_quad->Update();
	_col->Update();
	_hpImage->Update();
}

void Bow_Monster::Render()
{
	if (!isActive)
		return;

	_quad->Render();
	_col->Render();
	_hpImage->Render();
}

void Bow_Monster::Damaged(int damage)
{
	if (_hp == _maxHp)
		_hpImage->CreateMaterial(L"Resource/Texture/Dungreed/AED04.png");

	_hp -= damage;

	_hpImage->GetTransform()->GetScale() *= 0.9;

	if (_hp <= 0)
	{
		isActive = false;
		_col->isActive = false;
	}
}

void Bow_Monster::Revive()
{
	_hp = _maxHp;
	isActive = true;
	_col->isActive = true;
	_hpImage->CreateMaterial(L"Resource/Texture/Dungreed/AED01.png");
	_hpImage->GetTransform()->GetScale() = _hpImage->GetSize() * 0.5f;
}
