#include "framework.h"
#include "SceneManager.h"

#include "../Scene/BasicScene/TestScene.h"
#include "../Scene/BasicScene/MapEditorTestScene.h"
#include "../Scene/BasicScene/BossScene.h"
#include "../Scene/BasicScene/UIScene.h"

SceneManager* SceneManager::_instance = nullptr;
SceneManager::SceneManager()
{
	_sceneTable["TestScene"] = make_shared<TestScene>();
	_sceneTable["MapEditorTestScene"] = make_shared<MapEditorTestScene>();
	_sceneTable["BossScene"] = make_shared<BossScene>();
	_sceneTable["UIScene"] = make_shared<UIScene>();

	_curScene = _sceneTable["MapEditorTestScene"];
}

SceneManager::~SceneManager()
{
	_curScene = nullptr;
}

void SceneManager::Update()
{
	if (_curScene == nullptr) return;

	_curScene->Update();
	
	if (KEY_DOWN(VK_F3))
	{
		_curSceneIndex++;

		if (_curSceneIndex > 2)
			_curSceneIndex = 0;

		switch (_curSceneIndex)
		{
		case 0:
			SetScene("TestScene");
			break;
		case 1:
			SetScene("MapEditorTestScene");
			break;
		case 2:
			SetScene("BossScene");
			break;
		default:
			break;
		}
	}
	else if (KEY_DOWN(VK_F2))
	{
		_curSceneIndex--;

		if (_curSceneIndex < 0)
			_curSceneIndex = 2;

		switch (_curSceneIndex)
		{
		case 0:
			SetScene("TestScene");
			break;
		case 1:
			SetScene("MapEditorTestScene");
			break;
		case 2:
			SetScene("BossScene");
			break;
		default:
			break;
		}
	}

}

void SceneManager::Render()
{
	if (_curScene == nullptr) return;

	_curScene->Render();
}

void SceneManager::PreRender()
{
	if (_curScene == nullptr) return;

	_curScene->PreRender();
}

void SceneManager::PostRender()
{
	if (_curScene == nullptr) return;

	_curScene->PostRender();
}

void SceneManager::Init()
{
	_curScene->Init();
}

void SceneManager::SetScene(string name)
{
	if (_sceneTable.count(name) == 0)
		return;

	if (_curScene != nullptr)
	{
		_curScene->Fin();
	}
	_curScene = _sceneTable[name];
	_curScene->Init();
}
