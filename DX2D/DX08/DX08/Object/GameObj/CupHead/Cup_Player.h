#pragma once
class Cup_Player
{
public:
	enum State
	{
		CUP_IDLE,
		CUP_RUN,
		CUP_JUMP,
		CUP_DUCK,
		CUP_DUCK_IDLE,
		CUP_AIM_STRAIGHT_SHOT
	};

	Cup_Player();
	~Cup_Player();

	void Update();
	void Render();

	void SetRight();
	void SetLeft();

	void Input();
	void Jump();
	void Shot();

	void SetAction(State state);
	void SetIDLE();

	shared_ptr<Transform> GetTransform() { return _transform; }

private:
	void CreateAction(string name, Action::Type type);

	vector<wstring> _spritePaths;
	vector<string> _xmlPaths;

	shared_ptr<Transform> _transform;
	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	State _curState = State::CUP_IDLE;
	State _oldState = State::CUP_IDLE;

	float _floorHeight = 0.0f;
	float _speed = 300.0f;
	float _jumpSpeed = 1000.0f;

	bool _isJump = false;
	bool _isDuck = false;
};

