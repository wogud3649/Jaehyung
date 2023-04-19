#include "framework.h"
#include "Slider.h"

Slider::Slider()
{
	_quad = make_shared<Quad>(L"Resources/Texture/UI/HealthBar.png");
	_quad->SetPS(ADD_PS(L"Shader/UI/SliderPixelShader.hlsl"));

	_buffer = make_shared<SliderBuffer>();
	_buffer->_data.ratio = 1.0f;
}

Slider::~Slider()
{
}

void Slider::SetSlider(wstring file)
{
	_quad = make_shared<Quad>(file);
	_quad->SetPS(ADD_PS(L"Shader/UI/SliderPixelShader.hlsl"));
}

void Slider::Update()
{
	_quad->Update();
	_buffer->Update();
}

void Slider::PostRender()
{
	_buffer->SetPSBuffer(1);
	_quad->Render();
}

void Slider::SetPos(Vector2 pos)
{
	_quad->GetTransform()->SetPos(pos);
}

void Slider::SetScale(Vector2 scale)
{
}