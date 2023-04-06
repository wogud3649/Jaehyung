#include "framework.h"
#include "ObjectScene.h"

ObjectScene::ObjectScene()
{
}

ObjectScene::~ObjectScene()
{
}

void ObjectScene::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		_door = make_shared<Door>();
		_doorSpawn = true;
		_chest = make_shared<Chest>();
		_chestSpawn = true;
	}

	if (_chestSpawn)
	{
		_door->Update();
		_chest->Update();
	}
}

void ObjectScene::Render()
{
	if (_chestSpawn)
	{
		_chest->Render();
		_door->Render();
	}
}