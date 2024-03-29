#pragma once
class Cup_Bg
{
public:
	Cup_Bg();
	~Cup_Bg();

	void Update();
	void Render();

	void SetPos(Vector2 pos) { _bg->GetTransform()->GetPos() = pos; }
	void SetPlayer(shared_ptr<Cup_Advanced_Player> player);

	Vector2 LeftBottom();
	Vector2 RightTop();

private:
	shared_ptr<Quad> _bg;
	vector<shared_ptr<Cup_Track>> _tracks;
	
	weak_ptr<Cup_Advanced_Player> _player;
};

