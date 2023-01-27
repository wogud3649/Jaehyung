#include "framework.h"
#include "Bow.h"


Bow::Bow()
{
	_quad = make_shared<Quad>(L"Resource/Texture/Bow.png");
	_quad->GetTransform()->SetPos(Vector2(100, 100));
	_quad->GetTransform()->SetScale(Vector2(2, 2));

	for (int i = 0; i < _arrowSize; i++)
		_arrows.push_back(make_shared<Bow_Arrow>());
}

Bow::~Bow()
{
}

void Bow::Update()
{
	Vector2 direction = Vector2(MOUSE_POS.x - GetPos().x, MOUSE_POS.y - GetPos().y);
	_quad->GetTransform()->SetAngle(direction.Angle());

	if (KEY_DOWN(VK_LBUTTON))
	{
		Fire(direction);
	}

	_quad->Update();
	for (auto arrow : _arrows)
		arrow->Update();
}

void Bow::Render()
{
	_quad->Render();
	for (auto arrow : _arrows)
		arrow->Render();
}

void Bow::SetTarget(shared_ptr<Bow_Monster> target)
{
	for (auto arrow : _arrows)
		arrow->SetTarget(target);
}

void Bow::Fire(Vector2 direction)
{
	auto iter = find_if(_arrows.begin(), _arrows.end(), [](const shared_ptr<Bow_Arrow>& arrow)->bool
		{
			return (arrow->GetActive() == false);
		});
	if (iter != _arrows.end())
	{
		(*iter)->GetTransform()->SetPos(_quad->GetTransform()->GetPos());
		(*iter)->GetTransform()->SetAngle(direction.Angle());
		(*iter)->SetDirection(direction);
		(*iter)->EnAble();
	}
}