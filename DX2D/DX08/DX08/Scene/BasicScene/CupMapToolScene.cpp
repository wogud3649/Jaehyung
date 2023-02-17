#include "framework.h"
#include "CupMapToolScene.h"

CupMapToolScene::CupMapToolScene()
{
	_track = make_shared<Quad>(L"Resource/Texture/CupHead/clown_bg_track.png");
	_track->GetTransform()->GetScale() *= 0.5f;
	_track->GetTransform()->SetPosition(CENTER);
}

CupMapToolScene::~CupMapToolScene()
{
}

void CupMapToolScene::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
		_track->GetTransform()->SetPosition(MOUSE_POS);
	_track->Update();
}

void CupMapToolScene::Render()
{
	_track->Render();
}

void CupMapToolScene::PostRender()
{
	if (ImGui::Button("SAVE TrackPos", { 100, 30 }))
	{
		Save();
	}
}

void CupMapToolScene::Save()
{
	_trackPos = _track->GetTransform()->GetWorldPos();
	BinaryWriter writer = BinaryWriter(L"Save/CupHeadTrackPos.track");

	writer.Byte((void*)&_trackPos, sizeof(Vector2));
}

void CupMapToolScene::Load()
{
	Vector2 pos;
	Vector2* posPtr = &pos;
	BinaryReader reader = BinaryReader(L"Save/CupHeadTrackPos.track");
	reader.Byte((void**)&posPtr, sizeof(Vector2));


}
