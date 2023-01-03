#pragma once
class ArkanoidScene : public Scene
{
public:
	ArkanoidScene();
	virtual ~ArkanoidScene();

	void Update();
	void Render(HDC hdc);

private:
	shared_ptr<Arkanoid> _arkanoid;
};