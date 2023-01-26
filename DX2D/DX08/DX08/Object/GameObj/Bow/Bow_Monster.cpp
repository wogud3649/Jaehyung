#include "framework.h"
#include "Bow_Monster.h"

Bow_Monster::Bow_Monster()
{
	_quad = make_shared<Quad>(L"Resource/Texture/Monster.png");
	_quad->GetTransform()->GetScale() *= 0.7;
	_quad->GetTransform()->GetPos() = { WIN_WIDTH - 300, WIN_HEIGHT - 200 };

	_col = make_shared<CircleCollider>(100);
	_col->GetTransform()->SetParent(_quad->GetTransform());
	_col->GetTransform()->GetPos().x += 30;
	_col->GetTransform()->GetPos().y -= 20;
}

Bow_Monster::~Bow_Monster()
{
}

void Bow_Monster::Update()
{
	_quad->Update();
	_col->Update();


}

void Bow_Monster::Render()
{
	_quad->Render();
	//_col->Render();
}
