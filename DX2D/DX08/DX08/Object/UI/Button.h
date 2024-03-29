#pragma once
class Button
{
public:
	enum State
	{
		NONE,
		HOVER,
		CLICK
	};

	Button(wstring path);
	Button(Vector2 size);
	~Button();

	void Update();
	void PostRender();

	void SetPosition(Vector2 pos);
	void SetScale(Vector2 scale);

	void SetEvent(CallBack callBack) { _event = callBack; }
	void SetString(CallBack_String callBack) { _stringEvent = callBack; }

	Vector2 GetSize() { return _quad->GetImageSize(); }

	void SetParent(shared_ptr<Transform> transform) { GetTransform()->SetParent(transform); }
private:
	shared_ptr<Transform> GetTransform();
	State _state;

	shared_ptr<Quad> _quad;
	shared_ptr<Collider> _col;

	CallBack _event;
	CallBack_String _stringEvent;

	shared_ptr<ButtonBuffer> _buttonBuffer;
};

