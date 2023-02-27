#include "framework.h"
#include "Slider.h"

Slider::Slider(Vector2 size)
{
	_forward = make_shared<Quad>(L"Resource/Texture/UI/Button.png", size);
	_forward->SetPS(ADD_PS(L"Shader/UI/SliderPixelShader.hlsl"));
	_back = make_shared<Quad>(L"Resource/Texture/UI/Grey.png", size);

	_buffer = make_shared<SliderBuffer>();
	_buffer->_data.ratio = 0.5f;
}

Slider::~Slider()
{
}

void Slider::SetBack(wstring file, Vector2 size)
{
	_back = make_shared<Quad>(file, size);
}

void Slider::SetForward(wstring file, Vector2 size)
{
	_forward = make_shared<Quad>(file, size);
	_forward->SetPS(ADD_PS(L"Shader/UI/SliderPixelShader.hlsl"));
}

void Slider::SetPosition(Vector2 pos)
{
	_forward->GetTransform()->SetPos(pos);;
	_back->GetTransform()->SetPos(pos);;
}

void Slider::SetScale(Vector2 scale)
{
}

void Slider::Update()
{
	_forward->Update();
	_back->Update();
	_buffer->Update();
}

void Slider::PostRender()
{
	_buffer->SetPSBuffer(1);
	_back->Render();
	_forward->Render();
}
