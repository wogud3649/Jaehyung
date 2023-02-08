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
	shared_ptr<RectCollider> GetCollider() { return _col; }
	HIT_RESULT GetHIT_RESULT() { return result; }

private:
	shared_ptr<Quad> _track;
	shared_ptr<RectCollider> _col;
	HIT_RESULT result;

	weak_ptr<Cup_Advanced_Player> _player;
};