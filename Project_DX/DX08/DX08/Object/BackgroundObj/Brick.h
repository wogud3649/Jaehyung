#pragma once
class Brick
{
public:
	Brick();
	~Brick();

	void Update();
	void Render();
private:
	shared_ptr<Quad> _quad;
};

