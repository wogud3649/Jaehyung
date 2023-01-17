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
	shared_ptr<Transform> _virtual;

	vector<shared_ptr<Arrow>> _arrows;
	int _arrSize = 30;
};

