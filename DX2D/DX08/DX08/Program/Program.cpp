#include "framework.h"
#include "Program.h"



Program::Program()
{
	SCENE->Init();
}

Program::~Program()
{
}

void Program::Update()
{
	if (KEY_DOWN(VK_F1))
		Collider::isDebug = !Collider::isDebug;

	InputManager::GetInstance()->Update();
	TIMER->Update();
	AUDIO->Update();
	CAMERA->Update();

	SCENE->Update();
	EFFECT->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	CAMERA->SetCameraWorldBuffer();
	CAMERA->SetProjectionBuffer();
	SCENE->PreRender();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Device::GetInstance()->SetMainRenderTarget();

	ALPHA->SetState();

	SCENE->Render();
	EFFECT->Render();

	DirectWrite::GetInstance()->GetDC()->BeginDraw();

	wstring fps = L"FPS : " + to_wstring((int)Timer::GetInstance()->GetFPS());
	RECT rect = { 0,0,100,100 };
	DirectWrite::GetInstance()->RenderText(fps, rect);

	CAMERA->UICameraBuffer();
	CAMERA->PostRender();
	SCENE->PostRender();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	DirectWrite::GetInstance()->GetDC()->EndDraw();
	Device::GetInstance()->Present();
}
