#include "framework.h"
#include "Program.h"

#include "../Scene/TestScene.h"

Program::Program()
{
	_scene = make_shared<TestScene>();

	_view = make_shared<MatrixBuffer>();
	_proj = make_shared<MatrixBuffer>();

	XMMATRIX projMatrix = XMMatrixOrthographicOffCenterLH(0, WIN_WIDTH, 0, WIN_HEIGHT, 0.0f, 1.0f);

	_proj->SetData(projMatrix);

	_view->Update();
	_proj->Update();
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

	_scene->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	_view->SetVSBuffer(1);
	_proj->SetVSBuffer(2);
	_scene->PreRender();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ALPHA->SetState();

	_scene->Render();

	ImGui::Text("FPS : %d", Timer::GetInstance()->GetFPS());
	_scene->PostRender();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}
