#include "framework.h"
#include "Program.h"

#include "../Scene/TutorialScene.h"
#include "../Scene/SolarSystemScene.h"
#include "../Scene/BowScene.h"
#include "../Scene/CollisionScene.h"
#include "../Scene/MyGameScene.h"
#include "../Scene/SpriteScene.h"
#include "../Scene/ActionScene.h"
#include "../Scene/CupHeadScene.h"
#include "../Scene/EffectScene.h"

Program::Program()
{
	_scene = make_shared<CupHeadScene>();
}

Program::~Program()
{
}

void Program::Update()
{
	if (KEY_DOWN(VK_F1))
		Collider::isDebug = !Collider::isDebug;

	InputManager::GetInstance()->Update();
	Timer::GetInstance()->Update();
	Audio::GetInstance()->Update();
	Camera::GetInstance()->Update();

	_scene->Update();
	EFFECT->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	Camera::GetInstance()->SetCameraWorldBuffer();
	Camera::GetInstance()->SetProjectionBuffer();
	_scene->PreRender();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ALPHA->SetState();

	_scene->Render();
	EFFECT->Render();

	ImGui::Text("FPS : %d", Timer::GetInstance()->GetFPS());
	Camera::GetInstance()->PostRender();
	_scene->PostRender();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}
