#pragma once
class Background
{
public:
	Background();
	~Background();

	void Update();
	void BackgroundRender();

private:
	shared_ptr<Quad> _background;
};