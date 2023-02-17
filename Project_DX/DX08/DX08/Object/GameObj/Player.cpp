#include "framework.h"
#include "Player.h"

Player::Player()
{
	CreateAction("SKUL");

	_col = make_shared<CircleCollider>(30);

	for (auto sprite : _sprites)
		sprite->GetTransform()->SetParent(_col->GetTransform());

	_actions[State::IDLE]->Play();
}

Player::~Player()
{
}

void Player::Update()
{
	_col->Update();

	for (auto sprite : _sprites)
		sprite->Update();

	for (auto action : _actions)
		action->Update();
}

void Player::Render()
{
	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();
	_col->Render();
}

void Player::CreateAction(string skulType)
{
	wstring skulTypeW(skulType.begin(), skulType.end());
	string state;
	int frame;
	Action::Type type;

	for (int i = 0; i < State::StateSize; i++)
	{
		switch (i)
		{
		case 0:
			state = "IDLE";
			frame = 4;
			type = Action::Type::LOOP;
			break;
		case 1:
			state = "WALK";
			frame = 8;
			type = Action::Type::LOOP;
			break;
		case 2:
			state = "JUMP";
			frame = 2;
			type = Action::Type::END;
			break;
		case 3:
			state = "DASH";
			frame = 1;
			type = Action::Type::END;
			break;
		default:
			break;
		}
		wstring stateW(state.begin(), state.end());

		wstring srvPath = L"Resources/Texture/" + skulTypeW + L"/" + stateW + L".png";
		shared_ptr<SRV> srv = SRV_ADD(srvPath);

		Vector2 imageSize = srv->GetImageSize();
		Vector2 clipSize = Vector2(imageSize.x / frame, imageSize.y);

		shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, frame, imageSize * 3);
		_sprites.emplace_back(sprite);

		vector<Action::Clip> clips;

		float y = 0;
		float w = clipSize.x;
		float h = clipSize.y;

		for (int i = 0; i < frame; i++)
		{
			clips.emplace_back(w * i, y, w, h, SRV_ADD(srvPath));
		}

		string name = skulType + "_" + state;

		_actions.emplace_back(make_shared<Action>(clips, name, type));
	}
}

void Player::SetAction(State state)
{
	_curState = state;
	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}
