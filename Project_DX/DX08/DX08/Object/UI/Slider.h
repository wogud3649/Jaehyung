#pragma once
class Slider
{
public:
	Slider(Vector2 size);
	~Slider();

	void SetBack(wstring file, Vector2 size);
	void SetForward(wstring file, Vector2 size);

	void Update();
	void PostRender();

	void SetPos(Vector2 pos);
	void SetScale(Vector2 scale);

	void SetRatio(float value) { _buffer->_data.ratio = value; }

private:
	shared_ptr<Quad> _quad;
	shared_ptr<SliderBuffer> _buffer;
};

