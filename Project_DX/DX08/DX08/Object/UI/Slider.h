#pragma once
class Slider
{
public:
	Slider();
	Slider(wstring file);
	~Slider();

	void Update();
	void PostRender();

	void SetPos(Vector2 pos);

	void SetRatio(float value) { _buffer->_data.ratio = value; }
	void SetOpaque(float value) { _buffer->_data.opaque = value; }

private:
	shared_ptr<Quad> _quad;
	shared_ptr<SliderBuffer> _buffer;
};

