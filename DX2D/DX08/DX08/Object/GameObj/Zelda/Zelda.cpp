#include "framework.h"
#include "Zelda.h"

Zelda::Zelda()
{
	_sprite = make_shared<Sprite>(L"Resource/Texture/zelda.png", Vector2(10.0f, 8.0f), Vector2(700, 700));

	CreateAction();
	SetAction(_state);
	_curAction->Play();
}

Zelda::~Zelda()
{
}

void Zelda::Update()
{
	if (!KEY_PRESS('A') && !KEY_PRESS('W') && !KEY_PRESS('D') && !KEY_PRESS('S'))
	{
		if (KEY_UP('A'))
		{
			SetAction(State::LEFT_IDLE);
		}
		if (KEY_UP('W'))
		{
			SetAction(State::BACK_IDLE);
		}
		if (KEY_UP('D'))
		{
			SetAction(State::RIGHT_IDLE);
		}
		if (KEY_UP('S'))
		{
			SetAction(State::FRONT_IDLE);
		}
	}

	if (KEY_PRESS('A'))
	{
		_sprite->GetTransform()->GetPos().x -= _speed * DELTA_TIME;
		SetAction(State::LEFT_RUN);
	}
	if (KEY_PRESS('W'))
	{
		_sprite->GetTransform()->GetPos().y += _speed * DELTA_TIME;
		SetAction(State::BACK_RUN);
	}
	if (KEY_PRESS('D'))
	{
		_sprite->GetTransform()->GetPos().x += _speed * DELTA_TIME;
		SetAction(State::RIGHT_RUN);
	}
	if (KEY_PRESS('S'))
	{
		_sprite->GetTransform()->GetPos().y -= _speed * DELTA_TIME;
		SetAction(State::FRONT_RUN);
	}

	for (auto action : _actions)
		action->Update();
	_sprite->Update();
}

void Zelda::Render()
{
	_sprite->SetActionClip(_actions[_state]->GetCurClip());
	_sprite->Render();
}

void Zelda::SetAction(State state)
{
	_state = state;
	_curAction = _actions[_state];
	if (_oldAction != nullptr && _curAction->GetName() != _oldAction->GetName())
	{
		_oldAction->Reset();
		_curAction->Play();
	}
	_oldAction = _actions[_state];
}

void Zelda::SetPos(Vector2 pos)
{
	_sprite->GetTransform()->GetPos() = pos;
}

void Zelda::CreateAction()
{
	Vector2 imageSize = _sprite->GetImageSize();

	vector<Action::Clip> clips;

	float w = imageSize.x / 10.0f;
	float h = imageSize.y / 8.0f;
	float y = 0;

	// Front IDLE
	{
		y = 0;
		for (int i = 0; i < 3; i++)
		{
			clips.emplace_back(w * i, y, w, h, SRV_ADD(L"Resource/Texture/zelda.png"));
		}

		_actions.push_back(make_shared<Action>(clips, "Front_IDLE", Action::LOOP));
		clips.clear();
	}

	// Left IDLE
	{
		y = h;
		for (int i = 0; i < 3; i++)
		{
			clips.emplace_back(w * i, y, w, h, SRV_ADD(L"Resource/Texture/zelda.png"));
		}

		_actions.push_back(make_shared<Action>(clips, "Left_IDLE", Action::LOOP));
		clips.clear();
	}

	// Back IDLE
	{
		y = 2 * h;
		for (int i = 0; i < 1; i++)
		{
			clips.emplace_back(w * i, y, w, h, SRV_ADD(L"Resource/Texture/zelda.png"));
		}

		_actions.push_back(make_shared<Action>(clips, "Back_IDLE", Action::LOOP));
		clips.clear();
	}

	// Right IDLE
	{
		y = 3 * h;
		for (int i = 0; i < 3; i++)
		{
			clips.emplace_back(w * i, y, w, h, SRV_ADD(L"Resource/Texture/zelda.png"));
		}

		_actions.push_back(make_shared<Action>(clips, "Right_IDLE", Action::LOOP));
		clips.clear();
	}

	// RUN
	for (int j = 0; j < 4; j++)
	{
		y = h * (4 + j);
		for (int i = 0; i < 10; i++)
		{
			clips.emplace_back(w * i, y, w, h, SRV_ADD(L"Resource/Texture/zelda.png"));
		}

		switch (j)
		{
		case 0:
			_actions.push_back(make_shared<Action>(clips, "Front_RUN", Action::LOOP));
			break;
		case 1:
			_actions.push_back(make_shared<Action>(clips, "Left_RUN", Action::LOOP));
			break;
		case 2:
			_actions.push_back(make_shared<Action>(clips, "Back_RUN", Action::LOOP));
			break;
		case 3:
			_actions.push_back(make_shared<Action>(clips, "Right_RUN", Action::LOOP));
			break;
		default:
			break;
		}
		
		clips.clear();
	}
}
