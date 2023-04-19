#include "framework.h"
#include "Program.h"

Program::Program()
{
	srand(time(NULL));
	Timer::GetInstance()->SetLockFPS(60);
	SCENE->Init();
	STORE->SetCallBack();
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

	SCENE->PreRender();
	CAMERA->SetProjectBuffer();
	CAMERA->SetCameraWorldBuffer();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	DirectWrite::GetInstance()->GetDC()->BeginDraw();
	wstring fps = L"FPS : " + to_wstring((int)Timer::GetInstance()->GetFPS());
	RECT rect = { 0,0,100,100 };
	DirectWrite::GetInstance()->RenderText(fps, rect);

	ALPHA->SetState();

	SCENE->Render();
	EFFECT->Render();

	CAMERA->PostRender();
	CAMERA->UICameraBuffer();
	SCENE->PostRender();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	DirectWrite::GetInstance()->GetDC()->EndDraw();
	Device::GetInstance()->Present();
}