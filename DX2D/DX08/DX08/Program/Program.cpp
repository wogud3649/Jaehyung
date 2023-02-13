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
		Collider::isDebug = !Collider::isDebug;

	InputManager::GetInstance()->Update();
	Timer::GetInstance()->Update();

	_scene->Update();
	EFFECT->Update();
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
	EFFECT->Render();

	ImGui::Text("FPS : %d", Timer::GetInstance()->GetFPS());
	_scene->PostRender();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}
