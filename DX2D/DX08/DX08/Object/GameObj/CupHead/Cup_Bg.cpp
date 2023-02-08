#include "framework.h"
#include "Cup_Bg.h"

Cup_Bg::Cup_Bg()
{
	_bg = make_shared<Quad>(L"Resource/Texture/CupHead/clown_bg_main.png");
	
	for (int i = 0; i < 2; i++)
	{
		_tracks.emplace_back(make_shared<Cup_Track>());
		_tracks[i]->GetTransform()->SetParent(_bg->GetTransform());
	}
	_tracks[0]->GetTransform()->GetPos().y -= 300.0f;

	_tracks[1]->GetTransform()->GetPos() += Vector2(-1000.0f, -50.0f);
	_tracks[1]->GetCollider()->GetTransform()->GetScale().y *= 0.5f;
	_tracks[1]->GetCollider()->GetTransform()->GetPos().y += 25.0f;
}

Cup_Bg::~Cup_Bg()
{
}

void Cup_Bg::Update()
{
	_bg->Update();
	for (auto track : _tracks)
		track->Update();

	auto iter = find_if(_tracks.begin(), _tracks.end(), [](const shared_ptr<Cup_Track>& a)->bool
		{
			if (a->GetHIT_RESULT().isHit && a->GetHIT_RESULT().dir == Direction::UP)
				return true;
			return false;
		});

	if (iter == _tracks.end())
	{
		_player.lock()->Falling();
	}
}

void Cup_Bg::Render()
{
	_bg->Render();
	for (auto track : _tracks)
		track->Render();
}

void Cup_Bg::SetPlayer(shared_ptr<Cup_Advanced_Player> player)
{
	_player = player;

	for (auto track : _tracks)
		track->SetPlayer(player);
}
