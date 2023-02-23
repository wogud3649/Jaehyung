#include "framework.h"
#include "Button.h"

Button::Button(wstring path)
{
	_quad = make_shared<Quad>(path);
	_col = make_shared<RectCollider>(_quad->GetImageSize());
	_col->GetTransform()->SetParent(_quad->GetTransform());
}

Button::~Button()
{
}

void Button::Update()
{
	_col->Update();
	_quad->Update();

	if (_col->IsCollision(MOUSE_POS))
	{
		if (KEY_PRESS(VK_LBUTTON))
		{
			_col->SetRed();
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
	}
}

void Button::PostRender()
{
	_quad->Render();
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
