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
	bool IsPlay() { return _isPlay; }

	void SetCallBack(function<void(void)> event) { _endEvent = event; }

private:
	string _name;
	vector<Clip> _clips;

	Type _repeatType;
	bool _isPlay = true;
	UINT _curClipIndex = 0;

	float _time = 0.0f;
	float _speed = 0.0f;

	bool _isReverse = false; //

	// 콜백함수 : 정의는 미리 해둔 상태에서 나중에 내가 필요에 따라 호출할 수 있는 함수
	// 리스너 패턴 , 옵저버 패턴
	function<void(void)> _endEvent = nullptr;
};

