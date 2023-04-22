#pragma once
class FadePanel
{
public:
	FadePanel();
	~FadePanel();

	void Update();
	void PostRender();

	void StartFadeIn();
	void StartFadeOut();

	void SetColor(XMFLOAT3 color) { _color = color; }
	const float& GetDelay() { return _delay; }

private:
	void FadeIn();
	void FadeOut();
	shared_ptr<Quad> _filter;
	shared_ptr<ColorBuffer> _colorBuffer;

	XMFLOAT3 _color = { 0, 0, 0 };
	float _delay = 3.0f;
	bool _isFadeIn = false;
	bool _isFadeOut = false;
};

