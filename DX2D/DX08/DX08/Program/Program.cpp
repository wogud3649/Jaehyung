#include "framework.h"
#include "Program.h"

#include "../Scene/TutorialScene.h"
#include "../Scene/SolarSystemScene.h"

Program::Program()
{
	_scene = make_shared<SolarSystemScene>();

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
	_scene->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	_view->SetVSBuffer(1);
	_proj->SetVSBuffer(2);
	_scene->Render();

	Device::GetInstance()->Present();
}
