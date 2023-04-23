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
	if (_isAlive == false)
		return;

	_detectCol->Update();
	_standBodyCol->Update();
	_duckBodyCol->Update();
	_headCol->Update();

	_attackCol->Update();

	for (auto action : _actions)
		action->Update();
	for (auto sprite : _sprites)
		sprite->Update();

	if (_isDuck)
	{
		_curDuckDuration -= DELTA_TIME;
		if (_curDuckDuration <= 0.0f)
		{
			if (Stand())
				_curDuckDuration = _maxDuckDuration;
		}
	}

	Fall();

	Collision();
	Function();

	if (_curState == State::IDLE || _curState == State::DUCKIDLE)
	{
		_curIdleDuration -= DELTA_TIME;
		if (_curIdleDuration < 0.0f)
		{
			_curIdleDuration = _maxIdleDuration;
			Move();
		}
	}
}

void MushroomEnt::Render()
{
	if (_isAlive == false)
		return;

	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();

	_standBodyCol->Render();
	_duckBodyCol->Render();
	_headCol->Render();
	
	_detectCol->Render();
	_attackCol->Render();
}

void MushroomEnt::PostRender()
{
}

void MushroomEnt::Ground()
{
	_curJumpPower = 0.0f;
}

void MushroomEnt::Damaged(int damage, ATTRIBUTE attribute)
{
	_curHp -= damage;

	if (_curHp < 0.0f)
	{
		Dead();
		_curHp = 0;
	}
}

void MushroomEnt::Dead()
{
	_isAlive = false;
	INVENTORY->AddMoney(50);
}

void MushroomEnt::Function()
{
	if (_isAction)
		return;

	Walk();

	if (_curState != State::WALK && _curState != State::DUCKWALK)
	{
		if (_isDuck)
			SetAction(State::DUCKIDLE);
		else
			SetAction(State::IDLE);
	}
}

void MushroomEnt::Collision()
{
	Detect();
}

void MushroomEnt::Flip(Direction dir)
{
	if (_isAction)
		return;

	if (dir == Direction::RIGHT)
	{
		if (_direction == Direction::RIGHT)
			return;
		_direction = Direction::RIGHT;
		for (auto sprite : _sprites)
			sprite->SetDirection(_direction);
	}
	else if (dir == Direction::LEFT)
	{
		if (_direction == Direction::LEFT)
			return;
		_direction = Direction::LEFT;
		for (auto sprite : _sprites)
			sprite->SetDirection(_direction);
	}
}

void MushroomEnt::SetEdge(Direction dir)
{
	if (dir == Direction::RIGHT) _isRightEdge = true;
	else if (dir == Direction::LEFT) _isLeftEdge = true;
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

void MushroomEnt::Walk()
{
	if (_curState == State::WALK)
	{
		if (_direction == Direction::RIGHT && _isRightEdge == false)
			_standBodyCol->GetTransform()->MoveX(_moveSpeed * DELTA_TIME);
		else if (_direction == Direction::LEFT && _isLeftEdge == false)
			_standBodyCol->GetTransform()->MoveX(-_moveSpeed * DELTA_TIME);
	}
	else if (_curState == State::DUCKWALK)
	{
		if (_direction == Direction::RIGHT)
			_standBodyCol->GetTransform()->MoveX(_moveSpeed * 0.5f * DELTA_TIME);
		else
			_standBodyCol->GetTransform()->MoveX(-_moveSpeed * 0.5f * DELTA_TIME);
	}
}

void MushroomEnt::Duck()
{
	if (_isDuck == false)
	{
		_headCol->DeActivate();
		SetAction(State::DUCK);
		_isAction = true;
		_duckBodyCol->Activate();
	}
}

bool MushroomEnt::Stand()
{
	if (_isAction)
		return false;

	if (_isDuck)
	{
		SetAction(State::STAND);
		_isAction = true;
		_duckBodyCol->DeActivate();
	}

	return true;
}

void MushroomEnt::Fall()
{
	_standBodyCol->GetTransform()->MoveY(_curJumpPower * DELTA_TIME);
	_curJumpPower -= GRAVITY * GRAVITY * DELTA_TIME;
	if (_curJumpPower < -950.0f)
		_curJumpPower = -950.0f;
}

void MushroomEnt::Detect()
{
	HIT_RESULT result = _detectCol->SideCollision(PLAYER->GetFootCollider());
	
	if (result.isHit)
	{
		Flip(result.dir);

		if (abs(result.distance.x) < 200)
			Attack();
		else
			Move();
	}
}

void MushroomEnt::Move()
{
	if (_isAction)
		return;

	if (_isDuck)
		SetAction(State::DUCKWALK);
	else
		SetAction(State::WALK);
}

void MushroomEnt::Attack()
{
	if (_isAction)
		return;

	if (_isDuck)
		SetAction(State::DUCKATTACK);
	else
		SetAction(State::ATTACK);

	_isAction = true;
}

void MushroomEnt::AttackMid()
{
	_attackCol->GetTransform()->SetX(0);
	if (_direction == Direction::RIGHT)
	{
		_standBodyCol->GetTransform()->MoveX(150);
		_attackCol->GetTransform()->MoveX(-20);
		_attackCol->Activate();
	}
	else if (_direction == Direction::LEFT)
	{
		_standBodyCol->GetTransform()->MoveX(-150);
		_attackCol->GetTransform()->MoveX(20);
		_attackCol->Activate();
	}
	
	HIT_RESULT result = _attackCol->IsCollision(PLAYER->GetBodyCollider());
	if (result.isHit)
	{
		int damage = rand() % (_maxDamage - _minDamage) + _minDamage;
		PLAYER->Damaged(damage, _direction);
	}
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

void MushroomEnt::AttackEnd()
{
	SetIdle();
}

void MushroomEnt::AttackColEnd()
{
	_attackCol->DeActivate();
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
	_actions[State::ATTACK]->SetMidCallBack(std::bind(&MushroomEnt::AttackMid, this), 15);
	_actions[State::ATTACK]->SetMidCallBack(std::bind(&MushroomEnt::AttackColEnd, this), 16);

	_actions[State::DUCKATTACK]->SetMidCallBack(std::bind(&MushroomEnt::AttackMid, this), 12);
	_actions[State::DUCKATTACK]->SetMidCallBack(std::bind(&MushroomEnt::AttackColEnd, this), 13);

	_actions[State::ATTACK]->SetCallBack(std::bind(&MushroomEnt::AttackEnd, this));
	_actions[State::DUCK]->SetCallBack(std::bind(&MushroomEnt::DuckEnd, this));
	_actions[State::DUCKATTACK]->SetCallBack(std::bind(&MushroomEnt::AttackEnd, this));
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

	_detectCol = make_shared<RectCollider>(Vector2(800,100));
	_detectCol->GetTransform()->SetParent(_standBodyCol->GetTransform());
	_detectCol->GetTransform()->MoveY(10);

	_attackCol = make_shared<CircleCollider>(90);
	_attackCol->GetTransform()->SetParent(_standBodyCol->GetTransform());
	_attackCol->DeActivate();
}
