#include "framework.h"
#include "Arkanoid.h"

Arkanoid::Arkanoid()
{
	_bar = make_shared<Bar>();
	
	Vector2 offset = { 63.0f, 10.0f };

	for (int y = 0; y < poolCountY; y++)
	{
		for (int x = 0; x < poolCountX; x++)
		{
			shared_ptr<ArkBlock> block = make_shared<ArkBlock>();
			Vector2 distance = { 126.5f * x, 43.0f * y };
			block->GetCenter() = offset + distance;

			_blocks.push_back(block);
			_blockMatrix[y][x] = block;
		}
	}

	_items.reserve(5);
	for (int i = 0; i < 5; i++)
	{
		Vector2 temp = _blockMatrix[rand() % 5][rand() % 10]->GetCenter();
		shared_ptr<ArkItem> item = make_shared<ArkItem>(temp);
		_items.push_back(item);
	}
}

Arkanoid::~Arkanoid()
{
	for (int y = 0; y < poolCountY; y++)
	{
		for (int x = 0; x < poolCountX; x++)
		{
			_blockMatrix[y][x] = nullptr;
		}
	}
}

void Arkanoid::Update()
{
	for (auto& block : _blocks)
	{
		if (block->GetCollider()->IsCollision(_bar->GetBallInfo()->GetCollider()))
		{
			if (block->GetActive() == false)
				continue;
			if (block->GetCollider()->IsVCollision())
				_bar->GetBallInfo()->GetDirection().y *= -1;
			else if (block->GetCollider()->IsHCollision())
				_bar->GetBallInfo()->GetDirection().x *= -1;
			else
				_bar->GetBallInfo()->GetDirection() = (_bar->GetBallInfo()->GetCenter() - block->GetCenter()).NormalVector2();
			block->GetActive() = false;
		}
	}

	_bar->Update();
	for (auto& block : _blocks)
		block->Update();
	for (auto& item : _items)
		item->Update();
}

void Arkanoid::Render(HDC hdc)
{
	if (_bar->GetLife() == 0)
	{
		wstring lose = L"YOU LOSE";
		TextOut(hdc, CENTER_X - 50, CENTER_Y - 10, lose.c_str(), lose.size());
	}
	if (find_if(_blocks.begin(), _blocks.end(), [](const shared_ptr<ArkBlock>& a)->bool
		{
			return a->GetActive();
		}) == _blocks.end())
	{
		wstring win = L"YOU WIN!";
		TextOut(hdc, CENTER_X - 50, CENTER_Y - 10, win.c_str(), win.size());
	}
	wstring life = L"Life : "+ to_wstring(_bar->GetLife());
	TextOut(hdc, 0, CENTER_Y - 10, life.c_str(), life.size());

	_bar->Render(hdc);
	for (auto& block : _blocks)
		block->Render(hdc);
	for (auto& item : _items)
		item->Render(hdc);
}
