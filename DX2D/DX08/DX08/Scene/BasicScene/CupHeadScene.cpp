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

	_bg = make_shared<Cup_Bg>();
	_bg->SetPos(CENTER);
	_bg->SetPlayer(_player);

	AUDIO->Add("bgm", "Resource/Sound/BGM.mp3", true);
	AUDIO->Add("jump", "Resource/Sound/jump.wav");
	AUDIO->Stop("bgm");

	_button = make_shared<Button>(L"Resource/Texture/UI/Button.png");
	_button->SetScale({ 0.1f, 0.1f });
	_button->SetPosition(_button->GetSize() * 0.5f * 0.1f);
	_button->SetString(std::bind(&SceneManager::SetScene, SCENE, "SolarSystemScene"));

	_slider = make_shared<Slider>(Vector2(150, 50));
	_slider->SetPosition({ CENTER.x, CENTER.y - 100.0f });
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Init()
{
	Load();

	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->SetLeftBottom(_bg->LeftBottom());
	CAMERA->SetRightTop(_bg->RightTop());
	CAMERA->SetOffset(CENTER);

	AUDIO->Play("bgm");
	AUDIO->SetVolume("bgm", 0.5f);
}

void CupHeadScene::Finalize()
{
	AUDIO->Stop("bgm");
}

void CupHeadScene::Update()
{
	_bg->Update();
	_player->Update();
	_monster->Update();
	_button->Update();
	_slider->Update();
	_slider->SetRatio(_player->GetHp() / 100.0f);
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
	_player->PostRender();

	if (ImGui::Button("Save", { 100, 100 }));
	{
		Save();
	}

	if (ImGui::Button("NextScene", { 100,100 }))
	{
		SCENE->SetScene("SolarSystemScene");
	}

	_button->PostRender();
	_slider->PostRender();
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
