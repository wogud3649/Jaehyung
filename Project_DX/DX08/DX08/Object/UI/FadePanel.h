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

	void SetDelay(float delay) { _maxDelay = delay; _curDelay = _maxDelay; }
	void SetColor(XMFLOAT3 color) { _color = color; }
	const float& GetDelay() { return _curDelay; }

private:
	void FadeIn();
	void StartLoading();
	void Loading();
	void FadeOut();
	shared_ptr<Quad> _filter;
	shared_ptr<ColorBuffer> _colorBuffer;

	XMFLOAT3 _color = { 0, 0, 0 };
	float _maxDelay = 3.0f;
	float _curDelay = _maxDelay;

	bool _isFadeIn = false;
	bool _isFadeOut = false;
	bool _isLoading = false;
};

