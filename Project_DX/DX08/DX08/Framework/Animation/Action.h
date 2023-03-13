#pragma once
class Action
{
public:
	struct Clip
	{
		Vector2 _startPos;
		Vector2 _size;
		shared_ptr<SRV> _srv;

		Clip(float x, float y, float w, float h, shared_ptr<SRV> srv)
		: _startPos(x, y)
		, _size(w, h)
		, _srv(srv)
		{
		}
	};

	enum Type
	{
		END,
		LOOP,
		PINGPONG
	};

	Action(vector<Clip> clips, string name = "", Type type = LOOP, float speed = 0.1f);
	~Action();

	void Update();

	void Play();
	void Pause();
	void Stop();
	void Reset();

	Clip GetCurClip() { return _clips[_curClipIndex]; }
	Action::Type GetRepeatType() { return _repeatType; }
	string GetName() { return _name; }
	bool IsPlay() { return _isPlay; }

	void SetMidCallBack(function<void(void)> event) { _midEvent = event; }
	void SetCallBack(function<void(void)> event) { _endEvent = event; }

private:
	string _name;
	vector<Clip> _clips;

	Type _repeatType;
	bool _isPlay = false;
	UINT _curClipIndex = 0;

	float _time = 0.0f;
	float _speed = 0.0f;

	bool _isReverse = false;

	function<void(void)> _midEvent = nullptr;
	function<void(void)> _endEvent = nullptr;
};

