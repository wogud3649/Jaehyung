#include "framework.h"
#include "SceneManager.h"

#include "../Scene/BasicScene/TestScene.h"
#include "../Scene/BasicScene/MapEditorTestScene.h"
#include "../Scene/BasicScene/BossScene.h"
#include "../Scene/BasicScene/UIScene.h"
#include "../Scene/BasicScene/EffectScene.h"
#include "../Scene/BasicScene/MonsterScene.h"

SceneManager* SceneManager::_instance = nullptr;
SceneManager::SceneManager()
{
	_sceneTable["TestScene"] = make_shared<TestScene>();
	_sceneTable["MapEditorTestScene"] = make_shared<MapEditorTestScene>();
	_sceneTable["BossScene"] = make_shared<BossScene>();
	_sceneTable["EffectScene"] = make_shared<EffectScene>();
	_sceneTable["MonsterScene"] = make_shared<MonsterScene>();

	_curScene = _sceneTable["MapEditorTestScene"];
	_curSceneName = "MapEditorTestScene";
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
		_curSceneIndex++;
	else if (KEY_DOWN(VK_F2))
		_curSceneIndex--;

	if (_curSceneIndex != _oldSceneIndex)
	{
		if (_curSceneIndex > 4)
			_curSceneIndex = 0;
		else if (_curSceneIndex < 0)
			_curSceneIndex = 4;

		switch (_curSceneIndex)
		{
		case 0:
			dynamic_pointer_cast<TestScene>(_sceneTable["TestScene"])->SetScene(dynamic_pointer_cast<MapEditorTestScene>(_sceneTable["MapEditorTestScene"])->GetFilePath());
			SetScene("TestScene");
			_curSceneName = "TestScene";
			break;
		case 1:
			SetScene("MapEditorTestScene");
			_curSceneName = "MapEditorTestScene";
			break;
		case 2:
			SetScene("BossScene");
			_curSceneName = "BossScene";
			break;
		case 3:
			SetScene("EffectScene");
			_curSceneName = "EffectScene";
			break;
		case 4:
			SetScene("MonsterScene");
			_curSceneName = "MonsterScene";
			break;
		default:
			break;
		}

		_oldSceneIndex = _curSceneIndex;
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
	ImGui::Text(&_curSceneName[0]);
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
