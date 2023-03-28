#pragma once
class Pannel
{
public:
	Pannel();
	~Pannel();

	void Update();
	void Render();

private:
	shared_ptr<Quad> _quad;
};