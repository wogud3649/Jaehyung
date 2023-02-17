#pragma once
class Background
{
public:
	Background();
	~Background();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransform() { return _background->GetTransform(); }
private:
	shared_ptr<Quad> _background;
	vector<shared_ptr<Floor>> _floors;
	int _poolCountFloor = 1;
};

