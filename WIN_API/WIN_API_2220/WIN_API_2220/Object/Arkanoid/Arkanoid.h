#pragma once
class Arkanoid
{
public:
	Arkanoid();
	~Arkanoid();

	void Update();
	void Render(HDC hdc);

private:
	shared_ptr<Bar> _bar;

	const UINT poolCountX = 10;
	const UINT poolCountY = 5;

	vector<shared_ptr<ArkBlock>> _blocks;
	shared_ptr<ArkBlock> _blockMatrix[10][10] = { nullptr };
	
	vector<shared_ptr<ArkItem>> _items;
};