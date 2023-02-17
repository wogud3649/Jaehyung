#include "framework.h"
#include "SceneManager.h"

#include "../Scene/BasicScene/TutorialScene.h"
#include "../Scene/BasicScene/SolarSystemScene.h"
#include "../Scene/BasicScene/BowScene.h"
#include "../Scene/BasicScene/CollisionScene.h"
#include "../Scene/BasicScene/SpriteScene.h"
#include "../Scene/BasicScene/ActionScene.h"
#include "../Scene/BasicScene/CupHeadScene.h"
#include "../Scene/BasicScene/EffectScene.h"
#include "../Scene/BasicScene/CupMapToolScene.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager::SceneManager()
{
	_sceneTable["TutorialScene"] = make_shared<TutorialScene>();
	_sceneTable["SolarSystemScene"] = make_shared<SolarSystemScene>();
	_sceneTable["CupHeadScene"] = make_shared<CupHeadScene>();

	_curScene = _sceneTable["CupHeadScene"];
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

void SceneManager::SetScene(string name)
{
	if (_sceneTable.count(name) == 0)
		return;

	if (_curScene != nullptr)
	{
		_curScene->Finalize();
	}
	_curScene = _sceneTable[name];
	_curScene->Init();
}
