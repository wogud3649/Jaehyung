#pragma once
class BowScene :public Scene
{
public:
	BowScene();
	virtual ~BowScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Bow> _bow;
};

