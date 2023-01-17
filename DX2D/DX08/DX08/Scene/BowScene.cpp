#include "framework.h"
#include "BowScene.h"

BowScene::BowScene()
{
	_bow = make_shared<Bow>(L"Resource/Texture/Bow.png");
	_bow->SetPos(Vector2(CENTER_X, CENTER_Y));
	_bow->SetScale(Vector2(2.0f, 2.0f));

	for (int i = 0; i < _arrSize; i++)
	{
		_arrows.push_back(make_shared<Arrow>(L"Resource/Texture/Bullet.png"));
		_arrows[i]->SetParent(_bow->GetVirtualTransforms()[i]);
		_arrows[i]->SetScale(Vector2(0.1f, 0.1f));
	}
}

BowScene::~BowScene()
{
}

void BowScene::Update()
{
	float angle = Vector2(MOUSE_POS.x - CENTER_X, MOUSE_POS.y - CENTER_Y).Angle();

	_bow->GetTransform()->GetAngle() = angle;

	for (int i = 0; i < _arrSize; i++)
	{
		if (_arrows[i]->GetActive())
			continue;
		_bow->GetVirtualTransforms()[i]->GetAngle() = _bow->GetTransform()->GetAngle();
	}

	if (KEY_DOWN(VK_LBUTTON))
	{
		auto iter = find_if(_arrows.begin(), _arrows.end(), [](const shared_ptr<Arrow>& a)->bool
			{
				return (a->GetActive() == false);
			});
		if (iter != _arrows.end())
		{
			(*iter)->SetPos(Vector2(0.0f, 0.0f));
			(*iter)->SetActive(true);
		}
	}

	_bow->Update();
	for (int i = 0; i < _arrSize; i++)
	{
		_arrows[i]->Update();
	}
}

void BowScene::Render()
{
	_bow->Render();
	for (int i = 0; i < _arrSize; i++)
	{
		_arrows[i]->Render();
	}
}
