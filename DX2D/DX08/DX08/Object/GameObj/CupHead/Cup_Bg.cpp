#include "framework.h"
#include "Cup_Bg.h"

Cup_Bg::Cup_Bg()
{
	_bg = make_shared<Quad>(L"Resource/Texture/CupHead/clown_bg_main.png");
	_ground = make_shared<Quad>(L"Resource/Texture/CupHead/clown_bg_track.png");
	_ground->GetTransform()->SetParent(_bg->GetTransform());
	_ground->GetTransform()->GetPos().y -= 300.0f;
}

Cup_Bg::~Cup_Bg()
{
}

void Cup_Bg::Update()
{
	_bg->Update();
	_ground->Update();
}

void Cup_Bg::Render()
{
	_bg->Render();
	_ground->Render();
}
