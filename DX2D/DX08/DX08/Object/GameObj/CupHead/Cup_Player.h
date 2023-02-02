#pragma once
class Cup_Player
{
public:
	enum State
	{
		IDLE,
		RUN,
		JUMP,
		DUCK,
		DUCK_IDLE
	};
	enum Direction
	{
		RIGHT,
		LEFT
	};

	Cup_Player();
	~Cup_Player();

	void Update();
	void Render();

	void SetAction(State state);

	shared_ptr<Transform> GetTransform();

private:
	void CreatePath();
	void CreateSprite(int w, int h, int index);
	void CreateAction();
	void SetActionPos();
	void SetReverse(Direction direction);

	void Movement();
	void Jump();

	vector<wstring> _spritePaths;
	vector<string> _xmlPaths;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	State _state = State::IDLE;

	Direction _dir = Direction::RIGHT;

	float _speed = 300.0f;
	float _jumpSpeed = 1000.0f;

	bool _isJump = false;
	bool _isDuck = false;
};

