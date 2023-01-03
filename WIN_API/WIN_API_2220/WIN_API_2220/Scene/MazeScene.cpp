#include "framework.h"
#include "MazeScene.h"

MazeScene::MazeScene()
{
	_maze = make_shared<Maze>();
	_player = make_shared<Player>(_maze);
}

MazeScene::~MazeScene()
{
}

void MazeScene::Update()
{
	_maze->Update();
	_player->Update();
}

void MazeScene::Render(HDC hdc)
{
	_maze->Render(hdc);
}
