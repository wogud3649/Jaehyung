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
	Vector2 _backgroundSize;
	
	weak_ptr<Advanced_Player> _player;
};

