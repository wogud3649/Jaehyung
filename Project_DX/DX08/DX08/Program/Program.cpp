#include "framework.h"
#include "Program.h"

Program::Program()
{
	Timer::GetInstance()->SetLockFPS(60);
	SCENE->Init();
}

Program::~Program()
{
}

void Program::Update()
{
	if (KEY_DOWN(VK_F1))
		Collider::_isDebug = !Collider::_isDebug;

	InputManager::GetInstance()->Update();
	Timer::GetInstance()->Update();
	CAMERA->Update();

	SCENE->Update();
	EFFECT->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	CAMERA->SetProjectBuffer();
	CAMERA->SetCameraWorldBuffer();
	SCENE->PreRender();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::Text("FPS : %d", Timer::GetInstance()->GetFPS());

	ALPHA->SetState();

	SCENE->Render();
	EFFECT->Render();

	CAMERA->PostRender();
	CAMERA->UICameraBuffer();
	SCENE->PostRender();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}