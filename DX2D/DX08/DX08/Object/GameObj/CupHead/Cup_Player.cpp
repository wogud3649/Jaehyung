#include "framework.h"
#include "Cup_Player.h"

using namespace tinyxml2;

Cup_Player::Cup_Player()
{
	Init();
}

Cup_Player::~Cup_Player()
{
}

void Cup_Player::Update()
{
	Input();

	_sprites[_curState]->Update();
	_actions[_curState]->Update();
	_col->Update();

	_transform->UpdateSRT();

	for (auto bullet : _bullets)
		bullet->Update();
}

void Cup_Player::Render()
{
	for (auto bullet : _bullets)
		bullet->Render();

	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();
	_col->Render();
}

void Cup_Player::SetRight()
{
	_isRight = true;

	if (_dir == 0)
		return;
	_dir = 0;
	for (auto sprite : _sprites)
		sprite->GetLeftRight() = _dir;
}

void Cup_Player::SetLeft()
{
	_isRight = false;

	if (_dir == 1)
		return;
	_dir = 1;
	for (auto sprite : _sprites)
		sprite->GetLeftRight() = _dir;
}

void Cup_Player::Input()
{
	if (_isShooting)
		return;

	if (KEY_PRESS('A') && KEY_PRESS('D'))
	{
		if (!_isJump && !_isDuck)
			SetAction(State::CUP_IDLE);
	}
	else if (KEY_PRESS('A'))
	{
		SetLeft();
		if (!_isDuck)
		{
			_transform->GetPos().x -= _speed * DELTA_TIME;
			if (!_isJump)
				SetAction(State::CUP_RUN);
		}
	}
	else if (KEY_PRESS('D'))
	{
		SetRight();
		if (!_isDuck)
		{
			_transform->GetPos().x += _speed * DELTA_TIME;
			if (!_isJump)
				SetAction(State::CUP_RUN);
		}
	}
	if (KEY_UP('A') || KEY_UP('D'))
	{
		if (!_isDuck && !_isJump)
			SetAction(State::CUP_IDLE);
	}

	if (KEY_DOWN('S'))
	{
		if (!_isJump)
		{
			_isDucking = true;
			SetAction(State::CUP_DUCK);
			_actions[State::CUP_DUCK]->SetCallBack(std::bind(&Cup_Player::SetDuckIDLE, this));
		}
	}
	if (KEY_PRESS('S'))
	{
		if (!_isJump && !_isDucking)
			SetAction(State::CUP_DUCK_IDLE);
	}
	if (KEY_UP('S'))
	{
		if (!_isJump)
			SetAction(State::CUP_IDLE);
	}

	if (_curState == State::CUP_DUCK || _curState == State::CUP_DUCK_IDLE)
		_isDuck = true;
	else
		_isDuck = false;

	if (KEY_DOWN(VK_SPACE))
	{
		if (!_isJump)
		{
			_isJump = true;
			_floorHeight = _transform->GetPos().y;
			SetAction(State::CUP_JUMP);
		}
	}

	if (!_isDuck)
	{
		if (_isJump)
		{
			Jump();
		}
	}

	if (KEY_DOWN(VK_LBUTTON))
	{
		if (!_isDuck && !_isJump)
		{
			Shot();
		}
	}
}

void Cup_Player::Jump()
{
	_jumpSpeed -= 2000.0f * DELTA_TIME;
	_transform->GetPos().y += _jumpSpeed * DELTA_TIME;

	if (_transform->GetPos().y <= _floorHeight)
	{
		_transform->GetPos().y = _floorHeight;
		_isJump = false;
		_jumpSpeed = 1000.0f;
		SetAction(State::CUP_IDLE);
	}
}

void Cup_Player::Shot()
{
	auto iter = find_if(_bullets.begin(), _bullets.end(), [](const shared_ptr<Cup_Bullet>& a)->bool
		{
			return a->GetActive() == false;
		});
	if (iter != _bullets.end())
	{
		(*iter)->GetTransform()->GetPos() = _transform->GetPos();
		(*iter)->SetDirection(_dir);
		(*iter)->Enable();
		_actions[State::CUP_AIM_STRAIGHT_SHOT]->SetCallBack(std::bind(&Cup_Player::SetIDLE, this));
		SetAction(State::CUP_AIM_STRAIGHT_SHOT);
		_isShooting = true;
	}
}

void Cup_Player::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Cup_Player::SetIDLE()
{
	SetAction(State::CUP_IDLE);
	_isShooting = false;
}

void Cup_Player::SetDuckIDLE()
{
	_isDucking = false;
}

void Cup_Player::Init()
{
	CreateAction("Idle", Action::Type::LOOP);
	CreateAction("Run", Action::Type::LOOP);
	CreateAction("Jump", Action::Type::LOOP);
	CreateAction("Duck", Action::Type::END);
	CreateAction("DuckIdle", Action::Type::LOOP);
	CreateAction("AimStraightShot", Action::Type::END);
	
	_transform = make_shared<Transform>();

	for (int i = 0; i < bulletSize; i++)
		_bullets.emplace_back(make_shared<Cup_Bullet>());

	for (auto sprite : _sprites)
		sprite->GetTransform()->SetParent(_transform);

	_transform->GetScale() *= 0.7f;
	_col = make_shared<CircleCollider>(_characterSize.y / 5);
	_col->GetTransform()->SetParent(_transform);

	_actions[_curState]->Play();
}

void Cup_Player::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "CUP_" + name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type, 0.1f));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));

	if (_characterSize == Vector2(0, 0))
		_characterSize = xml.AverageSize();
}