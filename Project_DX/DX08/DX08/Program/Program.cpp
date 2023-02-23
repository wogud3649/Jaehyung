#include "framework.h"
#include "Program.h"

#include "../Scene/TestScene.h"

Program::Program()
{
	_scene = make_shared<TestScene>();
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

	_scene->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	CAMERA->SetCameraWorldBuffer();
	CAMERA->SetProjectBuffer();

	_scene->PreRender();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ALPHA->SetState();

	_scene->Render();

	ImGui::Text("FPS : %d", Timer::GetInstance()->GetFPS());
	CAMERA->PostRender();
	_scene->PostRender();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}
