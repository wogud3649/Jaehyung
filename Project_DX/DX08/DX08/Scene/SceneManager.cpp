#include "framework.h"
#include "SceneManager.h"

#include "../Scene/BasicScene/TestScene.h"
#include "../Scene/BasicScene/MapEditorTestScene.h"
#include "../Scene/BasicScene/GrassMapScene.h"
#include "../Scene/BasicScene/BossScene.h"

SceneManager* SceneManager::_instance = nullptr;
SceneManager::SceneManager()
{
	//_sceneTable["TestScene"] = make_shared<TestScene>();
	_sceneTable["MapEditorTestScene"] = make_shared<MapEditorTestScene>();
	//_sceneTable["BossScene"] = make_shared<BossScene>();

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
