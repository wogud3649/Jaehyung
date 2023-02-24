#include "framework.h"
#include "Button.h"

Button::Button(wstring path)
{
	_quad = make_shared<Quad>(path);
	_quad->SetPS(ADD_PS(L"Shader/UI/ButtonPixelShader.hlsl"));
	_col = make_shared<RectCollider>(_quad->GetImageSize());
	_col->GetTransform()->SetParent(_quad->GetTransform());

	_buttonBuffer = make_shared<ButtonBuffer>();

	_buttonBuffer->_data.hover = 0.3f;
	_buttonBuffer->_data.click = 0.6f;
}

Button::~Button()
{
}

void Button::Update()
{
	_col->Update();
	_quad->Update();
	_buttonBuffer->Update();

	if (_col->IsCollision(MOUSE_POS))
	{
		_state = State::HOVER;

		if (KEY_PRESS(VK_LBUTTON))
		{
			_col->SetRed();
			_state = State::CLICK;
		}

		if (KEY_UP(VK_LBUTTON))
		{
			if (_event != nullptr)
				_event();
			if (_stringEvent != nullptr)
				_stringEvent("NONE");
		}
	}
	else
	{
		_col->SetGreen();
		_state = State::NONE;
	}
}

void Button::PostRender()
{
	_quad->Render();

	_buttonBuffer->_data.state = static_cast<int>(_state);
	_buttonBuffer->SetPSBuffer(1);
	_col->Render();
}

void Button::SetPosition(Vector2 pos)
{
	_quad->GetTransform()->SetPosition(pos);
}

void Button::SetScale(Vector2 scale)
{
	_quad->GetTransform()->SetScale(scale);
}
