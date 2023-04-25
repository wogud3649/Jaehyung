#include "framework.h"
#include "FadePanel.h"

FadePanel::FadePanel()
{
	_filter = make_shared<Quad>(L"Resources/Texture/UI/Transparent.png");
	_filter->GetTransform()->SetPos(CENTER);
	_filter->SetPS(ADD_PS(L"Shader/ColorPixelShader.hlsl"));
	_colorBuffer = make_shared<ColorBuffer>();
	_colorBuffer->_data.color = { 0,0,0,0 };
}

FadePanel::~FadePanel()
{
}

void FadePanel::Update()
{
	_filter->Update();
	_colorBuffer->Update();

	FadeIn();
	FadeOut();
	Loading();
}

void FadePanel::PostRender()
{
	_colorBuffer->SetPSBuffer(2);
	_filter->Render();
}

void FadePanel::StartFadeIn()
{
	if (_isFadeIn)
		return;

	_isFadeIn = true;
}

void FadePanel::StartFadeOut()
{
	if (_isFadeOut)
		return;

	_isFadeOut = true;
}

void FadePanel::FadeIn()
{
	if (_isFadeIn == false)
		return;

	_curDelay -= DELTA_TIME;
	float ratio = _curDelay / _maxDelay;
	_colorBuffer->_data.color = { _color.x, _color.y, _color.z, 1 - ratio };

	if (_curDelay < 0)
	{
		_isFadeIn = false;
		_curDelay = _maxDelay;
		StartLoading();
	}
}

void FadePanel::StartLoading()
{
	if (_isLoading)
		return;

	_isLoading = true;
	_curDelay = 1.5f;
}

void FadePanel::Loading()
{
	if (_isLoading == false)
		return;

	_curDelay -= DELTA_TIME;
	if (_curDelay < 0)
	{
		_curDelay = _maxDelay;
		_isLoading = false;
		StartFadeOut();
	}
}

void FadePanel::FadeOut()
{
	if (_isFadeOut == false)
		return;

	_curDelay -= DELTA_TIME;
	float ratio = _curDelay / _maxDelay;
	_colorBuffer->_data.color = { _color.x, _color.y, _color.z, ratio };

	if (_curDelay < 0)
	{
		_isFadeOut = false;
		_curDelay = _maxDelay;
	}
}