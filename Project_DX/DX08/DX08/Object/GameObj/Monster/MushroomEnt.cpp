#include "framework.h"
#include "MushroomEnt.h"

MushroomEnt::MushroomEnt()
{
	SetColliders();
	SetSprites();
	CreateAction();
	SetCallback();

	_actions[_curState]->Play();
}

MushroomEnt::~MushroomEnt()
{
}

void MushroomEnt::Update()
{
	_standBodyCol->Update();
	_duckBodyCol->Update();
	_headCol->Update();

	for (auto action : _actions)
		action->Update();
	for (auto sprite : _sprites)
		sprite->Update();

	Collision();
	Function();
}

void MushroomEnt::Render()
{
	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();

	_standBodyCol->Render();
	_duckBodyCol->Render();
	_headCol->Render();
}

void MushroomEnt::Function()
{
	if (_isAction)
		return;

	Flip();

	if (KEY_PRESS(VK_LBUTTON))
	{
		if (_isDuck)
			SetAction(State::DUCKATTACK);
		else
			SetAction(State::ATTACK);
		_isAction = true;
	}
	else if (KEY_PRESS('S'))
	{
		if (_isDuck == false)
		{
			Duck();
		}
	}
	else if (KEY_PRESS('W'))
	{
		if (_isDuck)
		{
			SetAction(State::STAND);
			_isAction = true;
		}
	}
	else if (KEY_PRESS('D') || KEY_PRESS('A'))
	{
		if (_isDuck)
			SetAction(State::DUCKWALK);
		else
			SetAction(State::WALK);
	}
	else
	{
		if (_isDuck)
			SetAction(State::DUCKIDLE);
		else
			SetAction(State::IDLE);
	}
}

void MushroomEnt::Collision()
{
	if (_headCol->IsCollision(MOUSE_POS))
		Duck();

	if (_player.expired())
		return;

	if (_headCol->IsCollision(_player.lock()->GetFootCollider()) && _player.lock()->GetJumpPower() < 0.0f)
	{
		_player.lock()->Bounce();
		Duck();
	}
}

void MushroomEnt::Flip()
{
	if (KEY_PRESS('D'))
	{
		if (_direction == Direction::RIGHT)
			return;
		_direction = Direction::RIGHT;
		_sprites[_curState]->SetDirection(_direction);
	}
	if (KEY_PRESS('A'))
	{
		if (_direction == Direction::LEFT)
			return;
		_direction = Direction::LEFT;
		_sprites[_curState]->SetDirection(_direction);
	}
}

void MushroomEnt::SetAction(State state)
{
	_curState = state;
	if (_curState == _oldState)
		return;
	_sprites[_curState]->SetDirection(_direction);
	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_sprites[_oldState]->SetActionClip(_actions[_oldState]->GetCurClip());
	_oldState = _curState;
}

void MushroomEnt::SetIdle()
{
	if (_isDuck)
		SetAction(State::DUCKIDLE);
	else
		SetAction(State::IDLE);
	_isAction = false;
}

void MushroomEnt::Duck()
{
	_headCol->DeActivate();
	SetAction(State::DUCK);
	_isAction = true;
	_duckBodyCol->Activate();
}

void MushroomEnt::StandEnd()
{
	_headCol->Activate();
	_isDuck = false;
	SetIdle();
}

void MushroomEnt::DuckEnd()
{
	_isDuck = true;
	SetIdle();
}

void MushroomEnt::CreateAction()
{
	Vector2 imageSize;

	vector<Action::Clip> clips;

	float w;
	float h;
	float y;

	// IDLE
	{
		imageSize = _sprites[State::IDLE]->GetSize();

		w = imageSize.x / 7;
		h = imageSize.y;
		y = 0;

		for (int i = 0; i < 7; i++)
		{
			clips.emplace_back(w * i, y, w, h, SRV_ADD(L"Resources/Texture/MushroomEnt/IDLE_7x1.png"));
		}
		_actions.emplace_back(make_shared<Action>(clips, "IDLE", Action::LOOP));
		clips.clear();
	}

	// WALK
	{
		imageSize = _sprites[State::WALK]->GetClipSize();

		w = imageSize.x / 5;
		h = imageSize.y / 2;
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 5; x++)
			{
				clips.emplace_back(w * x, h * y, w, h, SRV_ADD(L"Resources/Texture/MushroomEnt/WALK_5x2.png"));
			}
		}
		_actions.emplace_back(make_shared<Action>(clips, "WALK", Action::LOOP));
		clips.clear();
	}

	// ATTACK
	{
		imageSize = _sprites[State::ATTACK]->GetClipSize();

		w = imageSize.x / 7;
		h = imageSize.y / 5;
		for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 7; x++)
			{
				clips.emplace_back(w * x, h * y, w, h, SRV_ADD(L"Resources/Texture/MushroomEnt/ATTACK_7x5.png"));
			}
		}
		_actions.emplace_back(make_shared<Action>(clips, "ATTACK", Action::END));
		clips.clear();
	}

	// DUCK
	{
		imageSize = _sprites[State::DUCK]->GetClipSize();

		w = imageSize.x / 19;
		h = imageSize.y;
		y = 0;
		for (int x = 0; x < 19; x++)
		{
			clips.emplace_back(w * x, y, w, h, SRV_ADD(L"Resources/Texture/MushroomEnt/DUCK_19x1.png"));
		}
		
		_actions.emplace_back(make_shared<Action>(clips, "DUCK", Action::END));
		clips.clear();
	}

	// DUCKIDLE
	{
		imageSize = _sprites[State::DUCKIDLE]->GetClipSize();

		w = imageSize.x / 4;
		h = imageSize.y / 2;
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				clips.emplace_back(w * x, h * y, w, h, SRV_ADD(L"Resources/Texture/MushroomEnt/DUCKIDLE_4x2.png"));
			}
		}
		_actions.emplace_back(make_shared<Action>(clips, "DUCKIDLE", Action::LOOP));
		clips.clear();
	}

	// DUCKWALK
	{
		imageSize = _sprites[State::DUCKWALK]->GetClipSize();

		w = imageSize.x / 5;
		h = imageSize.y / 2;
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 5; x++)
			{
				clips.emplace_back(w * x, h * y, w, h, SRV_ADD(L"Resources/Texture/MushroomEnt/DUCKWALK_5x2.png"));
			}
		}
		_actions.emplace_back(make_shared<Action>(clips, "DUCKWALK", Action::LOOP));
		clips.clear();
	}

	// DUCKATTACK
	{
		imageSize = _sprites[State::DUCKATTACK]->GetClipSize();

		w = imageSize.x / 11;
		h = imageSize.y / 3;
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 11; x++)
			{
				clips.emplace_back(w * x, h * y, w, h, SRV_ADD(L"Resources/Texture/MushroomEnt/DUCKATTACK_11x3.png"));
			}
		}
		_actions.emplace_back(make_shared<Action>(clips, "DUCKATTACK", Action::END));
		clips.clear();
	}

	// STAND
	{
		imageSize = _sprites[State::STAND]->GetClipSize();

		w = imageSize.x / 3;
		h = imageSize.y / 3;
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				clips.emplace_back(w * x, h * y, w, h, SRV_ADD(L"Resources/Texture/MushroomEnt/STAND_3x3.png"));
			}
		}
		_actions.emplace_back(make_shared<Action>(clips, "STAND", Action::END));
		clips.clear();
	}
}

void MushroomEnt::SetSprites()
{
	shared_ptr<Sprite> sprite = make_shared<Sprite>(L"Resources/Texture/MushroomEnt/IDLE_7x1.png", Vector2(7, 1), Vector2(987, 123));
	_sprites.emplace_back(sprite);

	sprite = make_shared<Sprite>(L"Resources/Texture/MushroomEnt/WALK_5x2.png", Vector2(5, 2), Vector2(710, 244));
	_sprites.emplace_back(sprite);

	sprite = make_shared<Sprite>(L"Resources/Texture/MushroomEnt/ATTACK_7x5.png", Vector2(7, 5), Vector2(1134, 685));
	_sprites.emplace_back(sprite);

	sprite = make_shared<Sprite>(L"Resources/Texture/MushroomEnt/DUCK_19x1.png", Vector2(19, 1), Vector2(3515, 126));
	_sprites.emplace_back(sprite);

	sprite = make_shared<Sprite>(L"Resources/Texture/MushroomEnt/DUCKIDLE_4x2.png", Vector2(4, 2), Vector2(627, 172));
	_sprites.emplace_back(sprite);

	sprite = make_shared<Sprite>(L"Resources/Texture/MushroomEnt/DUCKWALK_5x2.png", Vector2(5, 2), Vector2(785, 172));
	_sprites.emplace_back(sprite);

	sprite = make_shared<Sprite>(L"Resources/Texture/MushroomEnt/DUCKATTACK_11x3.png", Vector2(11, 3), Vector2(1826, 411));
	_sprites.emplace_back(sprite);

	sprite = make_shared<Sprite>(L"Resources/Texture/MushroomEnt/STAND_3x3.png", Vector2(3, 3), Vector2(486, 387));
	_sprites.emplace_back(sprite);

	for (auto sprite : _sprites)
	{
		sprite->GetTransform()->SetParent(_standBodyCol->GetTransform());
		sprite->GetTransform()->MoveY(25.0f);
	}

	_sprites[State::ATTACK]->GetTransform()->MoveY(5.0f);
	_sprites[State::DUCKIDLE]->GetTransform()->MoveY(-18.5f);
	_sprites[State::DUCKWALK]->GetTransform()->MoveY(-18.5f);
	_sprites[State::DUCKATTACK]->GetTransform()->MoveY(5.0f);
}

void MushroomEnt::SetCallback()
{
	_actions[State::ATTACK]->SetCallBack(std::bind(&MushroomEnt::SetIdle, this));
	_actions[State::DUCK]->SetCallBack(std::bind(&MushroomEnt::DuckEnd, this));
	_actions[State::DUCKATTACK]->SetCallBack(std::bind(&MushroomEnt::SetIdle, this));
	_actions[State::STAND]->SetCallBack(std::bind(&MushroomEnt::StandEnd, this));
}

void MushroomEnt::SetColliders()
{
	_standBodyCol = make_shared<CircleCollider>(40);
	_standBodyCol->GetTransform()->SetPos(CENTER);

	_headCol = make_shared<RectCollider>(Vector2(130, 20));
	_headCol->GetTransform()->SetParent(_standBodyCol->GetTransform());
	_headCol->GetTransform()->MoveY(55);

	_duckBodyCol = make_shared<CircleCollider>(60);
	_duckBodyCol->GetTransform()->SetParent(_standBodyCol->GetTransform());
	_duckBodyCol->DeActivate();
}
