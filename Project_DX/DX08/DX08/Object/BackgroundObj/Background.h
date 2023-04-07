#pragma once
class Background
{
public:
	Background();
	~Background();

	void Update();
	void BackgroundRender();

private:
	shared_ptr<Quad> _sky;
	shared_ptr<Quad> _trees;
};