#include "framework.h"
#include "Program.h"

#include "../Scene/PaintScene.h"
#include "../Scene/CollisionScene.h"
#include "../Scene/LineScene.h"
#include "../Scene/CannonScene.h"
#include "../Scene/ProjectionScene.h"
#include "../Scene/ArkanoidScene.h"
#include "../Scene/MazeScene.h"

HDC Program::_backBuffer = nullptr;

Program::Program()
{
	srand(static_cast<UINT>(time(nullptr)));
	HDC hdc = GetDC(hWnd);

	_backBuffer = CreateCompatibleDC(hdc);
	_hBit = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
	SelectObject(_backBuffer, _hBit);
	
	_sceneTable["Paint"] = make_shared<PaintScene>();
	_sceneTable["Collision"] = make_shared<CollisionScene>();
	_sceneTable["Line"] = make_shared<LineScene>();
	_sceneTable["Cannon"] = make_shared<CannonScene>();
	_sceneTable["Projection"] = make_shared<ProjectionScene>();
	_sceneTable["Arkanoid"] = make_shared<ArkanoidScene>();
	_sceneTable["Maze"] = make_shared<MazeScene>();

	_curScene = _sceneTable["Maze"];
}

Program::~Program()
{
	DeleteObject(_backBuffer);
	DeleteObject(_hBit);
}

void Program::Update()
{
	_curScene->Update();
}

void Program::Render(HDC hdc)
{
	PatBlt(_backBuffer, 0, 0, WIN_WIDTH, WIN_HEIGHT, BLACKNESS);

	_curScene->Render(_backBuffer);

	BitBlt(
		hdc, // 목적지
		0, 0, WIN_WIDTH, WIN_HEIGHT,
		_backBuffer, 0, 0, SRCCOPY // 복사할 정보
	);
}
