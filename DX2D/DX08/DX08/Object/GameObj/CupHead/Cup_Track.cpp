#include "framework.h"
#include "Cup_Track.h"

Cup_Track::Cup_Track()
{
	_track = make_shared<Quad>(L"Resource/Texture/CupHead/clown_bg_track.png");
	_col = make_shared<RectCollider>(Vector2(_track->GetImageSize().x, _track->GetImageSize().y * 0.45f));
	_col->GetTransform()->SetParent(_track->GetTransform());
}

Cup_Track::~Cup_Track()
{
}

void Cup_Track::Update()
{
	_col->Update();
	_track->Update();

	if (_player.expired() == false)
	{
		shared_ptr<CircleCollider> circle = _player.lock()->GetBodyCollider();
		result = _col->Block(circle);
		if (result.dir == Direction::LEFTUP || result.dir == Direction::RIGHTUP)
		{
			_player.lock()->Edge();
		}
		else if (result.dir == Direction::UP)
		{
			_player.lock()->Ground();
		}
		else if (result.dir == Direction::DOWN)
		{
			_player.lock()->Beat();
		}
	}
}

void Cup_Track::Render()
{
	_track->Render();
	_col->Render();
}
