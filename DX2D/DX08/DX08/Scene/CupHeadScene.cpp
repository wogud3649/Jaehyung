#include "framework.h"
#include "CupHeadScene.h"

CupHeadScene::CupHeadScene()
{
	_player = make_shared<Cup_Advanced_Player>();
	_player->GetBodyCollider()->GetTransform()->GetPos() = CENTER;
	_monster = make_shared<Cup_Monster>();
	_monster->GetTransform()->GetPos() = Vector2(WIN_WIDTH - 300.0f, CENTER.y);
	_monster->SetTarget(_player);
	_player->SetTarget(_monster);

	Load();

	_bg = make_shared<Cup_Bg>();
	_bg->SetPos(CENTER);
	_bg->SetPlayer(_player);

	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->SetLeftBottom(_bg->LeftBottom());
	CAMERA->SetRightTop(_bg->RightTop());
	CAMERA->SetOffset(CENTER);

	Audio::GetInstance()->Add("bgm", "Resource/Sound/BGM.mp3", true);
	Audio::GetInstance()->Add("jump", "Resource/Sound/jump.wav");
	Audio::GetInstance()->Play("bgm");
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Update()
{
	_bg->Update();
	_player->Update();
	_monster->Update();
}

void CupHeadScene::PreRender()
{
	_bg->Render();
}

void CupHeadScene::Render()
{
	_monster->Render();
	_player->Render();
}

void CupHeadScene::PostRender()
{
	if (ImGui::Button("Save", { 100, 100 }));
	{
		Save();
	}
}

void CupHeadScene::Save()
{
	BinaryWriter writer = BinaryWriter(L"Save/CupHeadInfo.cup");

	Vector2 pos = _player->GetTransform()->GetWorldPos();
	writer.Byte((void*)&pos, sizeof(Vector2));
}

void CupHeadScene::Load()
{
	BinaryReader reader = BinaryReader(L"Save/CupHeadInfo.cup");

	Vector2 pos;
	Vector2* posPtr = &pos;
	reader.Byte((void**)&posPtr, sizeof(Vector2));

	_player->GetTransform()->GetPos() = pos;
}
