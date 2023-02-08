#pragma once
class Cup_Track
{
public:
	Cup_Track();
	~Cup_Track();

	void Update();
	void Render();

	void SetPlayer(shared_ptr<Cup_Advanced_Player> player) { _player = player; }
	shared_ptr<Transform> GetTransform() { return _track->GetTransform(); }

private:
	shared_ptr<Quad> _track;
	shared_ptr<RectCollider> _col;

	weak_ptr<Cup_Advanced_Player> _player;
};