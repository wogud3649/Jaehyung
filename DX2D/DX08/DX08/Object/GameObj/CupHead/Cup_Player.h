#pragma once
class Cup_Player
{
public:
	enum State
	{
		IDLE,
		RUN
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

	vector<wstring> _spritePaths;
	vector<string> _xmlPaths;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<Action> _oldAction;
	shared_ptr<Action> _curAction;

	State _state = State::IDLE;
};

