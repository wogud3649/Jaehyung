#pragma once
class Background
{
public:
	Background();
	~Background();

	void Update();
	void Render();

	void SetPlayer(shared_ptr<Advanced_Player> player) { _player = player; }
	shared_ptr<Transform> GetTransform() { return _background->GetTransform(); }

	Vector2 LeftBottom();
	Vector2 RightTop();

private:
	shared_ptr<Quad> _background;
	vector<shared_ptr<Floor>> _floors;
	int _poolCountFloor = 4;
	
	weak_ptr<Advanced_Player> _player;
};

