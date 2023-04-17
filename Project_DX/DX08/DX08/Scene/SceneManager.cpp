#include "framework.h"
#include "SceneManager.h"

#include "../Scene/BasicScene/TestScene.h"
#include "../Scene/BasicScene/MapEditorTestScene.h"
#include "../Scene/BasicScene/UIScene.h"
#include "../Scene/BasicScene/EffectScene.h"
#include "../Scene/BasicScene/MonsterScene.h"
#include "../Scene/BasicScene/ObjectScene.h"
#include "../Scene/FieldScene/FieldScene1.h"
#include "../Scene/FieldScene/BossScene.h"
#include "../Scene/FieldScene/StoreScene.h"

SceneManager* SceneManager::_instance = nullptr;
SceneManager::SceneManager()
{
	_sceneTable["MapEditorTestScene"] = make_shared<MapEditorTestScene>();
	_sceneTable["TestScene"] = make_shared<TestScene>();
	_sceneTable["FieldScene1"] = make_shared<FieldScene1>();
	_sceneTable["StoreScene"] = make_shared<StoreScene>();
	_sceneTable["BossScene"] = make_shared<BossScene>();

	_curScene = _sceneTable["MapEditorTestScene"];
}

SceneManager::~SceneManager()
{
	_curScene = nullptr;
}

void SceneManager::Update()
{
	if (_curScene == nullptr) return;

	UI->Update();
	INVENTORY->Update();

	if (INVENTORY->IsOpen() == false)
	{
		_curScene->Update();
	}
	
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
			SetScene("MapEditorTestScene");
			break;
		case 1:
			dynamic_pointer_cast<TestScene>(_sceneTable["TestScene"])->SetScene(dynamic_pointer_cast<MapEditorTestScene>(_sceneTable["MapEditorTestScene"])->GetFilePath());
			SetScene("TestScene");
			break;
		case 2:
			SetScene("FieldScene1");
			break;
		case 3:
			SetScene("StoreScene");
			break;
		case 4:
			SetScene("BossScene");
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

	BACKGROUND->BackgroundRender();
	_curScene->PreRender();
}

void SceneManager::PostRender()
{
	if (_curScene == nullptr) return;

	_curScene->PostRender();

	if (_curSceneIndex != 0)
	{
		INVENTORY->PostRender();
		UI->PostRender();
		INTERACTOBJ->PostRender();
	}
}

void SceneManager::Init()
{
	INTERACTOBJ->GetChest()->SetRandom();
	INTERACTOBJ->GetDoor()->SetRandom();
	CAMERA->SetOffset(CENTER);
	UI->Init();
	DELTA_TIME = 0;
}

void SceneManager::Fin()
{
	CAMERA->SetTarget(nullptr);
}

void SceneManager::SetScene(string name)
{
	if (_sceneTable.count(name) == 0)
		return;

	if (_curScene != nullptr)
		_curScene->Fin();

	_curScene = _sceneTable[name];
	_curScene->Init();
}